/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:35:26 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/14 12:06:55 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_open_space(char **grid, int i, int j)
{
	char	c;

	c = grid[i][j];
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	handle_player(t_config *config, char dir, int i, int j)
{
	if (config->player.found)
		exit_error("Map validation error", "Multiple players found", NULL);
	config->player.found = 1;
	config->player.start_direction = dir;
	config->player.pos_x = j + 0.5;
	config->player.pos_y = i + 0.5;
}

static void	validate_cell(t_config *config, char **grid, int i, int j)
{
	if (!is_valid_map_char(grid[i][j]))
		exit_error("Map validation error", "Invalid character in map", NULL);
	if (grid[i][j] == 'N' || grid[i][j] == 'S'
		|| grid[i][j] == 'E' || grid[i][j] == 'W')
		handle_player(config, grid[i][j], i, j);
	if (is_open_space(grid, i, j))
	{
		if (i == 0 || !grid[i + 1] || j == 0 || grid[i][j + 1] == '\0')
			exit_error("Map validation error", "Open space at border", NULL);
		validate_enclosure(grid, i, j);
	}
}

int	validate_map_content(char **grid, t_config *config)
{
	int	i;
	int	j;

	if (!grid || !config || !config->map.grid)
		return (1);
	i = 0;
	while (grid[i])
	{
		j = 0;
		while (grid[i][j] && grid[i][j] == ' ')
			j++;
		if (grid[i][j] == '\0')
			exit_error("Map validation error", "Empty line in map", NULL);
		while (grid[i][j])
		{
			validate_cell(config, grid, i, j);
			j++;
		}
		i++;
	}
	if (!config->player.found)
		exit_error("Map validation error", "No player found in map", NULL);
	return (0);
}

void	validate_map(t_config *config)
{
	int	height;
	int	width;

	if (!config || !config->map.grid)
		exit_error("Map validation error", "Invalid map or config", NULL);
	height = config->map.height;
	width = config->map.width;
	if (validate_map_borders(config->map.grid, height, width))
		exit_error("Map validation error", "Error general borders map", NULL);
	if (validate_map_content(config->map.grid, config))
		exit_error("Map validation error", "Content error general map", NULL);
	validate_map_closed(config->map.grid, height, width);
}
