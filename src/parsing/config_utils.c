/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:16:17 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/12 20:28:20 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_config(t_config *config)
{
	ft_bzero(config, sizeof(t_config));
	config->win_width = RES_WINWIDHT;
	config->win_height = RES_WINHEIGHT;
	config->res_set = 1;
	config->map.grid = ft_calloc(MAX_MAP_HEIGHT + 1, sizeof(char *));
	if (!config->map.grid)
		exit_error("Memory error ", "Failed memory for map grid", NULL);
	config->map.width = 0;
	config->map.height = 0;
}

void	transfer_texture_paths(t_config *src, t_config *dest)
{
	dest->north_tex.path = ft_strdup(src->north_tex.path);
	dest->south_tex.path = ft_strdup(src->south_tex.path);
	dest->east_tex.path = ft_strdup(src->east_tex.path);
	dest->west_tex.path = ft_strdup(src->west_tex.path);
}

int	validate_texture_paths(t_config *config, t_config *src, t_mlx_vars *vars)
{
	if (!config->north_tex.path || !config->south_tex.path
		|| !config->east_tex.path || !config->west_tex.path)
	{
		free_config(src);
		exit_error("Memory error", "transfer_config", vars);
		return (0);
	}
	return (1);
}

void	copy_map_grid(t_config *src, t_config *dest, t_mlx_vars *vars)
{
	int	i;

	i = 0;
	dest->map.grid = malloc(sizeof(char *) * (src->map.height + 1));
	if (!dest->map.grid)
	{
		free_config(src);
		exit_error("Memory error", "map grid", vars);
	}
	while (i < src->map.height)
	{
		dest->map.grid[i] = ft_strdup(src->map.grid[i]);
		if (!dest->map.grid[i])
		{
			free_config(src);
			exit_error("Memory error", "map grid line", vars);
		}
		i++;
	}
	dest->map.grid[i] = NULL;
}

void	transfer_config_to_vars(t_config *src, t_mlx_vars *vars)
{
	t_config	*dest;

	if (!src || !vars)
		return ;
	dest = &vars->config;
	ft_bzero(dest, sizeof(t_config));
	dest->win_width = src->win_width;
	dest->win_height = src->win_height;
	dest->res_set = src->res_set;
	transfer_texture_paths(src, dest);
	if (!validate_texture_paths(dest, src, vars))
		return ;
	dest->floor_color = src->floor_color;
	dest->ceiling_color = src->ceiling_color;
	dest->map.width = src->map.width;
	dest->map.height = src->map.height;
	dest->player = src->player;
	dest->map.grid = NULL;
	if (src->map.grid)
		copy_map_grid(src, dest, vars);
	free_config(src);
}
