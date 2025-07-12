/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:01:04 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/07/09 20:01:04 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	validate_basic_config(t_config *config)
{
	if (!config)
		exit_error_parsing("Validation error", "Config is NULL", NULL);
	if (!config->res_set)
		exit_error_parsing("Validation error", "Resolution not set", config);
	if (!config->north_tex.path || !config->south_tex.path
		|| !config->east_tex.path || !config->west_tex.path)
		exit_error_parsing("Validation error", "Missing texture paths", config);
}

void	validate_colors_and_map(t_config *config)
{
	if (!config->floor_color.is_set || !config->ceiling_color.is_set)
		exit_error_parsing("Validation error",
			"Floor or ceiling color not set", config);
	if (!config->map.grid)
		exit_error_parsing("Validation error", "Map is missing", config);
	if (config->player.found != 1)
		exit_error_parsing("Validation error",
			"Invalid number of players", config);
}

void	validate_enclosure(char **grid, int i, int j, t_config *config)
{
	if (!grid[i - 1] || !grid[i + 1]
		|| !grid[i][j - 1] || !grid[i][j + 1]
		|| grid[i - 1][j] == ' '
		|| grid[i + 1][j] == ' '
		|| grid[i][j - 1] == ' '
		|| grid[i][j + 1] == ' ')
	{
		exit_error_parsing("map not closed", NULL, config);
	}
}

void	validate_scene_elements(t_config *config)
{
	validate_basic_config(config);
	validate_colors_and_map(config);
}
