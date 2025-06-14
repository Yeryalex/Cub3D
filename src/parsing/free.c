/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:47:47 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/12 18:48:28 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_texture_paths(t_config *config)
{
	free(config->north_tex.path);
	free(config->south_tex.path);
	free(config->east_tex.path);
	free(config->west_tex.path);
	config->north_tex.path = NULL;
	config->south_tex.path = NULL;
	config->east_tex.path = NULL;
	config->west_tex.path = NULL;
}

void	free_map_grid(t_config *config)
{
	int	i;

	i = 0;
	while (config->map.grid[i])
	{
		free(config->map.grid[i]);
		i++;
	}
	free(config->map.grid);
	config->map.grid = NULL;
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	free_texture_paths(config);
	if (config->map.grid)
		free_map_grid(config);
}
