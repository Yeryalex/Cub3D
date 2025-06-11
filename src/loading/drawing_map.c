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
	if (PLANES)
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
				put_pixel(x, y, 0, vars);
			x++;
		}
		y++;
	}
		return ;
	}
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

int get_texel_color(t_texture *tex, int x, int y)
{
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return 0;

	int offset = y * tex->line_length + x * (tex->bits_per_pixel / 8);
	int color = *(int *)(tex->addr + offset);
	return color;
}

void draw_line(t_mlx_vars *vars, int i, double start_x)
{
	t_player *player = &vars->config.player;

	double camera_x = 2 * i / (double)RES_WINWIDHT - 1;
	double ray_dir_x = player->dir_x + player->plane_x * camera_x;
	double ray_dir_y = player->dir_y + player->plane_y * camera_x;

	double	ray_x_planes = vars->config.player.pos_x;
	double	ray_y_planes = vars->config.player.pos_y;
	double	cos_angle = cos(start_x);
	double  sin_angle = sin(start_x);

	if (PLANES)
	{
		while (!ft_make_contact(ray_x_planes, ray_y_planes, vars))
		{
			
			put_pixel(ray_x_planes, ray_y_planes, 0xFF0000, vars);
			ray_x_planes += cos_angle;
			ray_y_planes += sin_angle;
		}
	}
	else
	{

	double ray_x = player->pos_x;
	double ray_y = player->pos_y;

	int map_x = (int)(ray_x / 64);
	int map_y = (int)(ray_y / 64);

	double side_dist_x, side_dist_y;
	double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(64 / ray_dir_x);
	double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(64 / ray_dir_y);

	int step_x, step_y;
	int side;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (ray_x - map_x * 64) * delta_dist_x / 64;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((map_x + 1) * 64 - ray_x) * delta_dist_x / 64;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (ray_y - map_y * 64) * delta_dist_y / 64;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((map_y + 1) * 64 - ray_y) * delta_dist_y / 64;
	}

	while (true)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1; 
		}
		if (vars->config.map.grid[map_y][map_x] == '1')
			break;
	}

	double wall_dist;
	if (side == 0)
		wall_dist = (map_x * 64 - ray_x + (step_x == -1 ? 64 : 0)) / ray_dir_x;
	else
		wall_dist = (map_y * 64 - ray_y + (step_y == -1 ? 64 : 0)) / ray_dir_y;
	double proj_plane_dist = (RES_WINWIDHT / 2.0) / tan(PI / 6);
	double wall_height = (64 / wall_dist) * proj_plane_dist;
	double start_y = (RES_WINHEIGHT - wall_height) / 2;
	double end_y = start_y + wall_height;

	if (start_y < 0) start_y = 0;
	if (end_y > RES_WINHEIGHT) end_y = RES_WINHEIGHT;

	double wall_x;
	if (side == 0)
		wall_x = ray_y + wall_dist * ray_dir_y;
	else
		wall_x = ray_x + wall_dist * ray_dir_x;
	wall_x = fmod(wall_x, 64);

	t_texture *tex;
	if (side == 0)
		tex = (ray_dir_x > 0) ? &vars->config.east_tex : &vars->config.west_tex;
	else
		tex = (ray_dir_y > 0) ? &vars->config.south_tex: &vars->config.north_tex;

	int tex_x = (int)(wall_x / 64.0 * tex->width);
	double tex_step = (double)tex->height / wall_height;
	double tex_pos = (start_y - (RES_WINHEIGHT - wall_height) / 2) * tex_step;

	for (int y = (int)start_y; y < (int)end_y; y++)
	{
		int tex_y = (int)tex_pos & (tex->height - 1);
		int color = get_texel_color(tex, tex_x, tex_y);
		put_pixel(i, y, color, vars);
		tex_pos += tex_step;
	}
	}
}


int drawing_loop(t_mlx_vars *vars)
{
	t_player *player = &vars->config.player;
	ft_move_player(player, vars);
	clear_image(vars);

	if (PLANES)
	{
		draw_square(player->pos_x, player->pos_y, 10, 0x00FF00, vars);
		draw_map(vars);
	}

	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
	double	fraction = PI / 3 / RES_WINWIDHT;
	double	start_x = vars->config.player.angle - PI / 6;

	for (int i = 0; i < RES_WINWIDHT; i++)
	{
		draw_line(vars, i, start_x);
		start_x += fraction;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
	return (0);
}