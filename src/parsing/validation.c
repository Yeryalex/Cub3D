/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:50:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/30 22:11:43 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_valid_cell(t_fill_info *info, int i, int j)
{
	if (i < 0 || i >= info->height || j < 0 || j >= info->width)
		return (0);
	if (!info->grid[i] || j >= (int)ft_strlen(info->grid[i]))
		return (0);
	if (info->visited[i][j] || info->grid[i][j] == '1')
		return (0);
	return (1);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

void	validate_scene_elements(t_config *config)
{
	if (!config)
		exit_error("Validation error", "Config is NULL", NULL);
	if (!config->res_set)
		exit_error("Validation error", "Resolution not set", NULL);
	if (!config->north_tex.path || !config->south_tex.path
		|| !config->east_tex.path || !config->west_tex.path)
		exit_error("Validation error", "Missing texture paths", NULL);
	if (!config->floor_color.is_set || !config->ceiling_color.is_set)
		exit_error("Validation error", "Floor or ceiling color not set", NULL);
	if (!config->map.grid)
		exit_error("Validation error", "Map is missing", NULL);
	if (config->player.found != 1)
		exit_error("Validation error", "Invalid number of players", NULL);
}

int	validate_map_borders(char **grid, int height, int width, t_config *config)
{
	int	i;
	int	j;

	if (!grid || height == 0 || width == 0)
		return (1);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (grid[i][j])
		{
			if ((i == 0 || i == height - 1 || j == 0 || 
				!grid[i][j + 1] || grid[i][j + 1] == '\0') &&
				(grid[i][j] == '0' || grid[i][j] == 'N' || 
				grid[i][j] == 'S' || grid[i][j] == 'E' || grid[i][j] == 'W'))
				exit_error_parsing("mapa no cerrado", "Espacio walkable en el borde", config);
			if (is_border_adjacent_to_walkable(grid, i, j, height, width))
				exit_error_parsing("mapa no cerrado", "Borde no protegido cerca de espacio walkable", config);
			j++;
		}
		i++;
	}
	return (0);
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
		exit_error_parsing("mapa no cerrado", NULL, config);
	}
}

static int	is_walkable_space(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_adjacent_walkable(char **grid, int i, int j, int height, int width)
{
	int	di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int	dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int	k;
	int	ni;
	int	nj;

	(void)width;
	k = 0;
	while (k < 8)
	{
		ni = i + di[k];
		nj = j + dj[k];
		if (ni >= 0 && ni < height && nj >= 0 && grid[ni] && 
			nj < (int)ft_strlen(grid[ni]) && is_walkable_space(grid[ni][nj]))
			return (1);
		k++;
	}
	return (0);
}

int	is_border_adjacent_to_walkable(char **grid, int i, int j, int height, int width)
{
	if (!grid || i < 0 || i >= height || j < 0 || !grid[i] || 
		j >= (int)ft_strlen(grid[i]))
		return (0);
	if (grid[i][j] != ' ')
		return (0);
	if (i == 0 || i == height - 1 || j == 0 || !grid[i][j + 1] || 
		grid[i][j + 1] == '\0')
		return (check_adjacent_walkable(grid, i, j, height, width));
	return (0);
}
