/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:50:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/07/09 20:13:56 by rbuitrag         ###   ########.fr       */
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

static void	check_border_cell(char **grid, int i, int j, t_config *config)
{
	int		height;
	char	c;

	height = config->map.height;
	c = grid[i][j];
	if ((i == 0 || i == height - 1 || j == 0 || !grid[i][j + 1]
		|| grid[i][j + 1] == '\0') && (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W'))
		exit_error_parsing("mapa no cerrado",
			"Espacio walkable en el borde", config);
	if (is_border_adjacent_to_walkable(grid, i, j, config))
		exit_error_parsing("mapa no cerrado",
			"Borde no protegido cerca de espacio walkable", config);
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
			check_border_cell(grid, i, j, config);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_border_adjacent_to_walkable(char **grid, int i, int j, t_config *config)
{
	int	height;

	height = config->map.height;
	if (!grid || i < 0 || i >= height || j < 0 || !grid[i]
		|| j >= (int)ft_strlen(grid[i]))
		return (0);
	if (grid[i][j] != ' ')
		return (0);
	if (i == 0 || i == height - 1 || j == 0 || !grid[i][j + 1]
		|| grid[i][j + 1] == '\0')
		return (check_adjacent_walkable(grid, i, j, config));
	return (0);
}
