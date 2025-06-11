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
	render->ray_x = player->pos_x;
	render->ray_y = player->pos_y;
	render->map_x = (int)(render->ray_x / 64);
	render->map_y = (int)(render->ray_y / 64);
	render->delta_dist_x = (render->ray_dir_x == 0) ? 1e30 : fabs(64 / render->ray_dir_x);
	render->delta_dist_y = (render->ray_dir_y == 0) ? 1e30 : fabs(64 / render->ray_dir_y);
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
		render->side_dist_x = (render->ray_x - render->map_x * 64) * render->delta_dist_x / 64;
	}
	else
	{
		render->step_x = 1;
		render->side_dist_x = ((render->map_x + 1) * 64 - render->ray_x) * render->delta_dist_x / 64;
	}
	if (render->ray_dir_y < 0)
	{
		render->step_y = -1;
		render->side_dist_y = (render->ray_y - render->map_y * 64) * render->delta_dist_y / 64;
	}
	else
	{
		render->step_y = 1;
		render->side_dist_y = ((render->map_y + 1) * 64 - render->ray_y) * render->delta_dist_y / 64;
	}
}

void	ft_DDA_loop(t_rendering_3d *render, t_mlx_vars *vars)
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
			break;
	}
}

void	ft_wall_distance(t_rendering_3d *render)
{
	if (render->side == 0)
		render->wall_dist = (render->map_x * 64 - render->ray_x + (render->step_x == -1 ? 64 : 0)) / render->ray_dir_x;
	else
		render->wall_dist = (render->map_y * 64 - render->ray_y + (render->step_y == -1 ? 64 : 0)) / render->ray_dir_y;

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

void	ft_texture_init(t_rendering_3d *render, t_mlx_vars *vars)
{
	if (render->side == 0)
		render->tex = (render->ray_dir_x > 0) ? &vars->config.east_tex : &vars->config.west_tex;
	else
		render->tex = (render->ray_dir_y > 0) ? &vars->config.south_tex: &vars->config.north_tex;

	render->tex_x = (int)(render->wall_x / 64.0 * render->tex->width);
	render->tex_step = (double)render->tex->height / render->wall_height;
	render->tex_pos = (render->start_y - (RES_WINHEIGHT - render->wall_height) / 2) * render->tex_step;
}

void	ft_print_texture(t_rendering_3d *render, int i, t_mlx_vars *vars)
{
	for (int y = (int)render->start_y; y < (int)render->end_y; y++)
	{
		int tex_y = (int)render->tex_pos & (render->tex->height - 1);
		int color = get_texel_color(render->tex, render->tex_x, tex_y);
		put_pixel(i, y, color, vars);
		render->tex_pos += render->tex_step;
	}
}