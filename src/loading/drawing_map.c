/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:28:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/31 13:54:27 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void put_pixel(int x, int y, int color, t_mlx_vars *game)
{
    if(x >= RES_WINWIDHT|| y >= RES_WINHEIGHT || x < 0 || y < 0)
        return;
    
    int index = y * game->line_length + x * game->bits_per_pixel / 8;
    game->addr[index] = color & 0xFF;
    game->addr[index + 1] = (color >> 8) & 0xFF;
    game->addr[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_mlx_vars *game)
{
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for(int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}

double distance(double x, double y){
    return sqrt(x * x + y * y);
}

double fixed_dist(double x1, double y1, double x2, double y2, t_mlx_vars *vars)
{
    double delta_x = x2 - x1;
    double delta_y = y2 - y1;
    double angle = atan2(delta_y, delta_x) - vars->config.player.angle;
    double fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}


void	ft_destroy_and_free(t_mlx_vars *vars)
{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_image(vars->mlx_ptr, vars->img_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		exit(0);
}

void	draw_map(t_mlx_vars *vars)
{
	char **map;

	map = vars->config.map.grid;
	for (int y = 0; map[y]; y++)
		for (int x = 0; map[y][x]; x++)
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, 0xFFAAFF, vars);
}

bool ft_make_contact(double px, double py, t_mlx_vars *vars)
{
    int x = px / 64;
    int y = py / 64;
	if (vars->config.map.grid[y][x] == '1')
        return true;
    return false;
}

void	clear_image(t_mlx_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < RES_WINHEIGHT)
	{
		x = 0;
		while (x < RES_WINWIDHT)
		{
			if (y < RES_WINHEIGHT / 2)
				put_pixel(x, y, 0x87CEEB, vars);
			else
				put_pixel(x, y, 0x5F8A0F, vars); 
			x++;
		}
		y++;
	}
}



void	draw_line(t_mlx_vars *vars, double start_x, int i)
{
	double	ray_x = vars->config.player.pos_x;
	double	ray_y = vars->config.player.pos_y;
	double	cos_angle = cos(start_x);
	double  sin_angle = sin(start_x);

	while (!ft_make_contact(ray_x, ray_y, vars))
	{
		if (PLANES)
			put_pixel(ray_x, ray_y, 0xFF0000, vars);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	if (!PLANES)
	{
		double dist = fixed_dist(vars->config.player.pos_x, vars->config.player.pos_y, ray_x, ray_y, vars);
		double height = (64 / dist) * (RES_WINWIDHT/ 2);
		double start_y = (RES_WINHEIGHT - height) / 2;
		int end = start_y + height;
		while (start_y < end)
		{
			put_pixel(i, start_y, 0x59614A, vars);
			start_y++;
		}
	}
}


int	drawing_loop(t_mlx_vars *vars)
{
	t_player *player;

	player = &vars->config.player;
	ft_move_player(player, vars);
	clear_image(vars);
	if (PLANES)
	{
		draw_square(vars->config.player.pos_x, vars->config.player.pos_y, 10, 0x00FF00, vars);
		draw_map(vars);
	}
	double	fraction = PI / 3 / RES_WINWIDHT;
	double	start_x = vars->config.player.angle - PI / 6;
	int i = 0;
	while (i < RES_WINWIDHT)
	{
		//draw_line(player, vars, start_x, i);
		draw_line(vars, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
	return (0);
}