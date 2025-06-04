/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_maps_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:24:50 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/16 11:47:27 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_valid_cell(char **grid, int i, int j, int height)
{
    if (i < 0 || i >= height)
        return (0);
    if (j < 0 || !grid[i][j])
        return (0);
    return (1);
}

static void	flood_fill(char **grid, int **visited, int i, int j, int height)
{
    if (!is_valid_cell(grid, i, j, height))
        return;
    if (visited[i][j] || grid[i][j] == '1')
        return;
    visited[i][j] = 1;
    if (grid[i][j] == ' ' || grid[i][j] == '\0')
    {
        flood_fill(grid, visited, i + 1, j, height);
        flood_fill(grid, visited, i - 1, j, height);
        flood_fill(grid, visited, i, j + 1, height);
        flood_fill(grid, visited, i, j - 1, height);
    }
}
static void	flood_borders(char **grid, int **visited, int height)
{
    int	i;
	int	last;

    i = 0;
    while (i < height)
    {
        if (grid[i][0] && grid[i][0] != '1')
            flood_fill(grid, visited, i, 0, height);
        last = 0;
        while (grid[i][last])
            last++;
        if (last > 0 && grid[i][last - 1] != '1')
            flood_fill(grid, visited, i, last - 1, height);
        i++;
    }
}

static void	flood_top_bottom(char **grid, int **visited, int height)
{
    int	i;

    i = 0;
    while (grid[0][i])
    {
        if (grid[0][i] != '1')
            flood_fill(grid, visited, 0, i, height);
        i++;
    }
    i = 0;
    while (grid[height - 1][i])
    {
        if (grid[height - 1][i] != '1')
            flood_fill(grid, visited, height - 1, i, height);
        i++;
    }
}

static void	check_flood(char **grid, int **visited, int height)
{
    int	i;
	int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (grid[i][j])
        {
            if ((grid[i][j] == '0' || grid[i][j] == 'N' || grid[i][j] == 'S'
                || grid[i][j] == 'E' || grid[i][j] == 'W') && visited[i][j])
                exit_error("Map validation error ", "Map is not closed (flood fill)", NULL);
            j++;
        }
        i++;
    }
}

static void	free_visited(int **visited, int height)
{
    int	i;

    i = 0;
    while (i < height)
        free(visited[i++]);
    free(visited);
}

void	validate_map_closed(char **grid, int height, int width)
{
    int	**visited;
    int	i;

    visited = malloc(sizeof(int *) * height);
    if (!visited)
        exit_error("Memory error ", "Flood fill visited malloc", NULL);
    i = 0;
    while (i < height)
    {
        visited[i] = calloc(width, sizeof(int));
        if (!visited[i])
            exit_error("Memory error ", "Flood fill visited row malloc", NULL);
        i++;
    }
    flood_borders(grid, visited, height);
    flood_top_bottom(grid, visited, height);
    check_flood(grid, visited, height);
    free_visited(visited, height);
}