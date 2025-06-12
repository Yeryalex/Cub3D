/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrodrigu <yrodrigu@student.42barcelo>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:13:37 by yrodrigu          #+#    #+#             */
/*   Updated: 2025/06/12 14:40:47 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_init_3d_vars(t_rendering_3d *render, t_player *player, int i)
{
	render->camera_x = 2 * i / (double)RES_WINWIDHT - 1;
	render->ray_dir_x = player->dir_x + player->plane_x * render->camera_x;
	render->ray_dir_y = player->dir_y + player->plane_y * render->camera_x;
	render->ray_x = player->pos_x;
	render->ray_y = player->pos_y;
	render->map_x = (int)(render->ray_x / 64);
	render->map_y = (int)(render->ray_y / 64);
	if (render->ray_dir_x == 0)
		render->delta_dist_x = 1e30;
	else
		render->delta_dist_x = fabs(64 / render->ray_dir_x);
	if (render->ray_dir_y == 0)
		render->delta_dist_y = 1e30;
	else
		render->delta_dist_y = fabs(64 / render->ray_dir_y);
	render->proj_plane_dist = (RES_WINWIDHT / 2.0) / tan(PI / 6);
	render->wall_height = (64 / render->wall_dist) * render->proj_plane_dist;
	render->start_y = (RES_WINHEIGHT - render->wall_height) / 2;
	render->end_y = render->start_y + render->wall_height;
}

void	ft_ray_direction(t_rendering_3d *render)
{
	if (render->ray_dir_x < 0)
	{
		render->step_x = -1;
		render->side_dist_x = (render->ray_x - render->map_x * 64)
			* render->delta_dist_x / 64;
	}
	else
	{
		render->step_x = 1;
		render->side_dist_x = ((render->map_x + 1) * 64 - render->ray_x)
			* render->delta_dist_x / 64;
	}
	if (render->ray_dir_y < 0)
	{
		render->step_y = -1;
		render->side_dist_y = (render->ray_y - render->map_y * 64)
			* render->delta_dist_y / 64;
	}
	else
	{
		render->step_y = 1;
		render->side_dist_y = ((render->map_y + 1) * 64 - render->ray_y)
			* render->delta_dist_y / 64;
	}
}

void	ft_dda_loop(t_rendering_3d *render, t_mlx_vars *vars)
{
	while (true)
	{
		if (render->side_dist_x < render->side_dist_y)
		{
			render->side_dist_x += render->delta_dist_x;
			render->map_x += render->step_x;
			render->side = 0;
		}
		else
		{
			render->side_dist_y += render->delta_dist_y;
			render->map_y += render->step_y;
			render->side = 1;
		}
		if (vars->config.map.grid[render->map_y][render->map_x] == '1')
			break ;
	}
}

void	ft_wall_distance(t_rendering_3d *render)
{
	if (render->side == 0)
	{
		if (render->step_x == -1)
			render->step_x = 64;
		else
			render->step_x = 0;
		render->wall_dist = (render->map_x * 64
				- render->ray_x + render->step_x) / render->ray_dir_x;
	}
	else
	{
		if (render->step_y == -1)
			render->step_y = 64;
		else
			render->step_y = 0;
		render->wall_dist = (render->map_y * 64
				- render->ray_y + render->step_y) / render->ray_dir_y;
	}
	if (render->start_y < 0)
		render->start_y = 0;
	if (render->end_y > RES_WINHEIGHT)
		render->end_y = RES_WINHEIGHT;
}

void	ft_distance_for_texture(t_rendering_3d *render)
{
	if (render->side == 0)
		render->wall_x = render->ray_y + render->wall_dist * render->ray_dir_y;
	else
		render->wall_x = render->ray_x + render->wall_dist * render->ray_dir_x;
	render->wall_x = fmod(render->wall_x, 64);
}
