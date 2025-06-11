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
	t_rendering_3d render;
	
	if (PLANES)
		ft_render_2d(vars, start_x);
	else
	{
		ft_init_3d_vars(&render, player, i);


	double side_dist_x, side_dist_y;

	int step_x, step_y;
	int side;

	if (render.ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (render.ray_x - render.map_x * 64) * render.delta_dist_x / 64;
	}
	else
	{
		step_x = 1;
		side_dist_x = ((render.map_x + 1) * 64 - render.ray_x) * render.delta_dist_x / 64;
	}
	if (render.ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (render.ray_y - render.map_y * 64) * render.delta_dist_y / 64;
	}
	else
	{
		step_y = 1;
		side_dist_y = ((render.map_y + 1) * 64 - render.ray_y) * render.delta_dist_y / 64;
	}

	while (true)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += render.delta_dist_x;
			render.map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += render.delta_dist_y;
			render.map_y += step_y;
			side = 1; 
		}
		if (vars->config.map.grid[render.map_y][render.map_x] == '1')
			break;
	}

	if (side == 0)
		render.wall_dist = (render.map_x * 64 - render.ray_x + (step_x == -1 ? 64 : 0)) / render.ray_dir_x;
	else
		render.wall_dist = (render.map_y * 64 - render.ray_y + (step_y == -1 ? 64 : 0)) / render.ray_dir_y;



	if (render.start_y < 0) render.start_y = 0;
	if (render.end_y > RES_WINHEIGHT) render.end_y = RES_WINHEIGHT;

	if (side == 0)
		render.wall_x = render.ray_y + render.wall_dist * render.ray_dir_y;
	else
		render.wall_x = render.ray_x + render.wall_dist * render.ray_dir_x;
	render.wall_x = fmod(render.wall_x, 64);

	// t_texture *tex;
	// if (side == 0)
	// 	tex = (ray_dir_x > 0) ? &vars->config.east_tex : &vars->config.west_tex;
	// else
	// 	tex = (ray_dir_y > 0) ? &vars->config.south_tex: &vars->config.north_tex;

	// int tex_x = (int)(wall_x / 64.0 * tex->width);
	// double tex_step = (double)tex->height / wall_height;
	// double tex_pos = (start_y - (RES_WINHEIGHT - wall_height) / 2) * tex_step;

	for (int y = (int)render.start_y; y < (int)render.end_y; y++)
	{
		// int tex_y = (int)tex_pos & (tex->height - 1);
		// int color = get_texel_color(tex, tex_x, tex_y);
		put_pixel(i, y, 0, vars);
	//	tex_pos += tex_step;
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