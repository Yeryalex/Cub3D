/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_2D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:13:37 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/06/11 12:14:55 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	clear_image(t_mlx_vars *vars)
{
	if (PLANES)
	{
		ft_clear_2D(vars);
		return ;
	}
	ft_clear_3D(vars);
}

void	ft_destroy_and_free(t_mlx_vars *vars)
{
		mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
		mlx_destroy_image(vars->mlx_ptr, vars->img_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
		exit(0);
}

bool ft_make_contact(double px, double py, t_mlx_vars *vars)
{
    int x = px / 64;
    int y = py / 64;
	if (vars->config.map.grid[y][x] == '1')
        return true;
    return false;
}

void	ft_render_2d(t_mlx_vars *vars, double start_x)
{
	t_rendering_2d render;

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



void	ft_init_3d_vars(t_rendering_3d *render, t_player *player, int i)
{
	render->camera_x = 2 * i / (double)RES_WINWIDHT - 1;
	render->ray_dir_x = player->dir_x + player->plane_x * render->camera_x;
	render->ray_dir_y = player->dir_y + player->plane_y * render->camera_x;
	// render->ray_x = player->pos_x;
	// render->ray_y = player->pos_y;
	// render->map_x = (int)(render->ray_x / 64);
	// render->map_y = (int)(render->ray_y / 64);
	// render->delta_dist_x = (render->ray_dir_x == 0) ? 1e30 : fabs(64 / render->ray_dir_x);
	// render->delta_dist_y = (render->ray_dir_y == 0) ? 1e30 : fabs(64 / render->ray_dir_y);
	// render->proj_plane_dist = (RES_WINWIDHT / 2.0) / tan(PI / 6);
}