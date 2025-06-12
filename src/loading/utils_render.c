/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:13:37 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/06/12 14:49:27 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	clear_image(t_mlx_vars *vars)
{
	if (PLANES)
	{
		ft_clear_2d(vars);
		return ;
	}
	ft_clear_3d(vars);
}

bool	ft_make_contact(double px, double py, t_mlx_vars *vars)
{
	int	x;
	int	y;

	x = px / 64;
	y = py / 64;
	if (vars->config.map.grid[y][x] == '1')
		return (true);
	return (false);
}

void	ft_texture_init(t_rendering_3d *render, t_mlx_vars *vars)
{
	if (render->side == 0)
	{
		if (render->ray_dir_x > 0)
			render->tex = &vars->config.east_tex;
		else
			render->tex = &vars->config.west_tex;
	}
	else
	{
		if (render->ray_dir_y > 0)
			render->tex = &vars->config.south_tex;
		else
			render->tex = &vars->config.north_tex;
	}
	render->tex_x = (int)(render->wall_x / 64.0 * render->tex->width);
	render->tex_step = (double)render->tex->height / render->wall_height;
	render->tex_pos = (render->start_y
			- (RES_WINHEIGHT - render->wall_height) / 2) * render->tex_step;
}

void	ft_print_texture(t_rendering_3d *render, int i, t_mlx_vars *vars)
{
	int	y;
	int	tex_y;
	int	color;

	y = (int)render->start_y;
	while (y < (int)render->end_y)
	{
		tex_y = (int)render->tex_pos & (render->tex->height - 1);
		color = get_texel_color(render->tex, render->tex_x, tex_y);
		put_pixel(i, y, color, vars);
		render->tex_pos += render->tex_step;
		y++;
	}
}
