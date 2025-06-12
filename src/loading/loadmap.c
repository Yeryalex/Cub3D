/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:00:08 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/12 14:49:55 by yrodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_texture(t_texture *tex, void *mlx, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		ft_putstr_fd("Error loading texture: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr,
			&tex->bits_per_pixel,
			&tex->line_length,
			&tex->endian);
	tex->path = path;
}

int	load_textures(t_mlx_vars *vars)
{
	load_texture(&vars->config.north_tex, vars->mlx_ptr,
		vars->config.north_tex.path);
	load_texture(&vars->config.south_tex, vars->mlx_ptr,
		vars->config.south_tex.path);
	load_texture(&vars->config.east_tex, vars->mlx_ptr,
		vars->config.east_tex.path);
	load_texture(&vars->config.west_tex, vars->mlx_ptr,
		vars->config.west_tex.path);
	return (0);
}

void	ft_axis_player(t_player *player)
{
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}
