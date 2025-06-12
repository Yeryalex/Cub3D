/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:13:37 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/06/12 12:28:26 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_render_2d(t_mlx_vars *vars, double start_x)
{
	t_rendering_2d	render;

	render.ray_x_planes = vars->config.player.pos_x;
	render.ray_y_planes = vars->config.player.pos_y;
	render.cos_angle = cos(start_x);
	render.sin_angle = sin(start_x);
	while (!ft_make_contact(render.ray_x_planes, render.ray_y_planes, vars))
	{
		put_pixel(render.ray_x_planes, render.ray_y_planes, 0xFF0000, vars);
		render.ray_x_planes += render.cos_angle;
		render.ray_y_planes += render.sin_angle;
	}
}

void	draw_square(int x, int y, int size, t_mlx_vars *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, 0xFFAAFF, game);
		put_pixel(x, y + i, 0xFFAAFF, game);
		put_pixel(x + size, y + i, 0xFFAAFF, game);
		put_pixel(x + i, y + size, 0xFFAAFF, game);
		i++;
	}
}

void	draw_map(t_mlx_vars *vars)
{
	char	**map;
	int		y;
	int		x;

	y = 0;
	map = vars->config.map.grid;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, vars);
			x++;
		}
		y++;
	}
}

void	ft_clear_2d(t_mlx_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < RES_WINHEIGHT)
	{
		x = 0;
		while (x < RES_WINWIDHT)
		{
			put_pixel(x, y, 0, vars);
			x++;
		}
		y++;
	}
}

void	ft_clear_3d(t_mlx_vars *vars)
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
