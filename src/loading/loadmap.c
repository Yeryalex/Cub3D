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

static void	print_texture_error(char *path, char *direction)
{
	printf("Error\n");
	if (path)
		printf("Texture file not found: %s\n", path);
	else
		printf("%s texture path is NULL\n", direction);
}

int	validate_texture_files(t_config *config)
{
	if (!config->north_tex.path || access(config->north_tex.path, F_OK) != 0)
	{
		print_texture_error(config->north_tex.path, "North");
		return (ERROR);
	}
	if (!config->south_tex.path || access(config->south_tex.path, F_OK) != 0)
	{
		print_texture_error(config->south_tex.path, "South");
		return (ERROR);
	}
	if (!config->east_tex.path || access(config->east_tex.path, F_OK) != 0)
	{
		print_texture_error(config->east_tex.path, "East");
		return (ERROR);
	}
	if (!config->west_tex.path || access(config->west_tex.path, F_OK) != 0)
	{
		print_texture_error(config->west_tex.path, "West");
		return (ERROR);
	}
	return (SUCCESS);
}

void	load_texture(t_texture *tex, void *mlx, char *path, t_mlx_vars *vars)
{
	tex->img_ptr = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
		exit_error("Error loading texture", path, vars);
	tex->addr = mlx_get_data_addr(tex->img_ptr,
			&tex->bits_per_pixel,
			&tex->line_length,
			&tex->endian);
	tex->path = path;
}

int	load_textures(t_mlx_vars *vars)
{
	load_texture(&vars->config.north_tex, vars->mlx_ptr,
		vars->config.north_tex.path, vars);
	load_texture(&vars->config.south_tex, vars->mlx_ptr,
		vars->config.south_tex.path, vars);
	load_texture(&vars->config.east_tex, vars->mlx_ptr,
		vars->config.east_tex.path, vars);
	load_texture(&vars->config.west_tex, vars->mlx_ptr,
		vars->config.west_tex.path, vars);
	return (0);
}

void	ft_axis_player(t_player *player)
{
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}
