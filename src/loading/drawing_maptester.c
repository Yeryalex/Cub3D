/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 10:28:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/05 19:38:14 by rbuitrag         ###   ########.fr       */
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
				put_pixel(x, y, vars->config.ceiling_color.combined, vars);
			else
				put_pixel(x, y, vars->config.floor_color.combined, vars); 
			x++;
		}
		y++;
	}
}


int	get_texture_color(t_texture *tex, int x, int y)
{
    int	offset;

	if (!tex || !tex->addr)
		return (0x000000); 
    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    if (x >= tex->width)
        x = tex->width - 1;
    if (y >= tex->height)
        y = tex->height - 1;
    offset = y * tex->line_length + x * (tex->bits_per_pixel / 8);
    return (*(int *)(tex->addr + offset));
}

t_texture	*select_wall_texture(t_mlx_vars *vars, int side, double ray_dir_x, double ray_dir_y)
{
    if (side == 0)
    {
        if (ray_dir_x > 0)
            return (&vars->config.east_tex);
        else
            return (&vars->config.west_tex);
    }
    else
    {
        if (ray_dir_y > 0)
            return (&vars->config.south_tex);
        else
            return (&vars->config.north_tex);
    }
}

void	draw_wall_texture(t_mlx_vars *vars, int x, double start_y, double height, t_texture *tex, double wall_x)
{
    int		y;
    int		tex_x;
    int		tex_y;
    double	step;
    double	tex_pos;

	if (!tex || !tex->addr)
        return; 
    tex_x = (int)(wall_x * (double)tex->width);
    step = 1.0 * tex->height / height;
    tex_pos = 0.0;
    y = (int)start_y;
    while (y < start_y + height && y < RES_WINHEIGHT)
    {
        tex_y = (int)tex_pos;
        put_pixel(x, y, get_texture_color(tex, tex_x, tex_y), vars);
        tex_pos += step;
        y++;
    }
}

// Sustituye tu draw_line por esta versión:
void	draw_line(t_mlx_vars *vars, double start_x, int i)
{
    double	ray_x = vars->config.player.pos_x;
    double	ray_y = vars->config.player.pos_y;
    double	cos_angle = cos(start_x);
    double  sin_angle = sin(start_x);
    int side = 0;
    double	step = 1.0;
    double	wall_x;
    double	dist_x, dist_y;

    // DDA simple para encontrar la pared y el lado de impacto
    while (!ft_make_contact(ray_x, ray_y, vars))
    {
        dist_x = fabs((floor(ray_x / 64 + 1) * 64 - ray_x) / cos_angle);
        dist_y = fabs((floor(ray_y / 64 + 1) * 64 - ray_y) / sin_angle);
        if (dist_x < dist_y)
        {
            ray_x += cos_angle * step;
            side = 0;
        }
        else
        {
            ray_y += sin_angle * step;
            side = 1;
        }
        ray_x += cos_angle * step;
        ray_y += sin_angle * step;
    }
    if (!PLANES)
    {
        double dist = fixed_dist(vars->config.player.pos_x, vars->config.player.pos_y, ray_x, ray_y, vars);
        double height = (64 / dist) * (RES_WINWIDHT / 2);
        double start_y = (RES_WINHEIGHT - height) / 2;

        // Calcular wall_x (pos de impacto en la pared)
        if (side == 0)
            wall_x = fmod(ray_y / 64.0, 1.0);
        else
            wall_x = fmod(ray_x / 64.0, 1.0);

        t_texture *tex = select_wall_texture(vars, side, cos_angle, sin_angle);
        draw_wall_texture(vars, i, start_y, height, tex, wall_x);
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
		draw_square(vars->config.player.pos_x, vars->config.player.pos_y, 10, vars->config.floor_color.combined, vars);
		draw_map(vars);
	}
	double	fraction = PI / 3 / RES_WINWIDHT;
	double	start_x = vars->config.player.angle - PI / 6;
	int i = 0;
	while (i < RES_WINWIDHT)
	{
		draw_line(vars, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
	return (0);
}