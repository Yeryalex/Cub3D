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

void draw_maze(t_mlx_vars *vars, int i, double start_x)
{
	t_player *player = &vars->config.player;
	t_rendering_3d render;
	
	if (PLANES)
		ft_render_2d(vars, start_x);
	else
	{
		ft_init_3d_vars(&render, player, i);
		ft_ray_direction(&render);
		ft_DDA_loop(&render, vars);
		ft_wall_distance(&render);
		ft_distance_for_texture(&render);
		ft_texture_init(&render, vars);
		ft_print_texture(&render, i, vars);
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
		draw_maze(vars, i, start_x);
		start_x += fraction;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_ptr, 0, 0);
	return (0);
}