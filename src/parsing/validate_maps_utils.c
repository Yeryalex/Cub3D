/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_maps_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:24:50 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/12 19:56:54 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	flood_fill(t_fill_info *info, int i, int j)
{
	if (!is_valid_cell(info, i, j))
		return;
	if (info->grid[i][j] != ' ')
		return;
	info->visited[i][j] = 1;
	flood_fill(info, i + 1, j);
	flood_fill(info, i - 1, j);
	flood_fill(info, i, j + 1);
	flood_fill(info, i, j - 1);
}

static void	flood_borders(t_fill_info *info)
{
	int	i;
	int	last;

	i = 0;
	while (i < info->height)
	{
		if (info->grid[i][0] && info->grid[i][0] != '1')
			flood_fill(info, i, 0);
		last = 0;
		while (info->grid[i][last])
			last++;
		if (last > 0 && info->grid[i][last - 1] != '1')
			flood_fill(info, i, last - 1);
		i++;
	}
}

static void	flood_top_bottom(t_fill_info *info)
{
	int	i;

	i = 0;
	while (info->grid[0][i])
	{
		if (info->grid[0][i] != '1')
			flood_fill(info, 0, i);
		i++;
	}
	i = 0;
	while (info->grid[info->height - 1][i])
	{
		if (info->grid[info->height - 1][i] != '1')
			flood_fill(info, info->height - 1, i);
		i++;
	}
}

static void	check_flood(t_fill_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->height)
	{
		j = 0;
		while (info->grid[i][j])
		{
			if ((info->grid[i][j] == '0' || info->grid[i][j] == 'N'
				|| info->grid[i][j] == 'S' || info->grid[i][j] == 'E'
				|| info->grid[i][j] == 'W') && info->visited[i][j])
				exit_error("Map validation error",
					"Map is not closed (flood fill)", NULL);
			j++;
		}
		i++;
	}
}

void	validate_map_closed(char **grid, int height, int width)
{
	t_fill_info	info;
	int			i;

	info.grid = grid;
	info.height = height;
	info.width = width;
	info.visited = malloc(sizeof(int *) * height);
	if (!info.visited)
		exit_error("Memory error", "Flood fill visited malloc", NULL);
	i = 0;
	while (i < height)
	{
		info.visited[i] = calloc(width, sizeof(int));
		if (!info.visited[i])
			exit_error("Memory error", "Flood fill visited row malloc", NULL);
		i++;
	}
	flood_borders(&info);
	flood_top_bottom(&info);
	check_flood(&info);
	free_visited(info.visited, height);
}
