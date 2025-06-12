/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:50:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/12 19:56:35 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_valid_cell(t_fill_info *info, int i, int j)
{
	if (i < 0 || i >= info->height || j < 0 || j >= info->width)
		return (0);
	if (info->visited[i][j] || info->grid[i][j] == '1')
		return (0);
	return (1);
}

int	is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

void	validate_scene_elements(t_config *config)
{
    if (!config)
        exit_error("Validation error", "Config is NULL", NULL);
    printf ("Textura NORTH: %s\n", config->north_tex.path);
    printf ("Textura SOUTH: %s\n", config->south_tex.path);
    printf ("Textura EAST: %s\n", config->east_tex.path);
    printf ("Textura WEST: %s\n", config->west_tex.path);
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

int	validate_map_borders(char **grid, int height, int width)
{
    int i;

    i = 0;
    if (!grid || height == 0 || width == 0)
        return (1);
    while (grid[0][i])
    {
        if (grid[0][i] != '1' && grid[0][i] != ' ')
            exit_error("Map validation error", "Map is not closed at the top", NULL);
        i++;
    }
    i = 0;
    while (grid[height - 1][i])
    {
        if (grid[height - 1][i] != '1' && grid[height - 1][i] != ' ')
            exit_error("Map validation error", "Map is not closed at the bottom", NULL);
        i++;
    }
    return (0);
}

void	validate_enclosure(char **grid, int i, int j)
{
    if (!grid[i - 1] || !grid[i + 1] ||
        !grid[i][j - 1] || !grid[i][j + 1] ||
        grid[i - 1][j] == ' ' ||
        grid[i + 1][j] == ' ' ||
        grid[i][j - 1] == ' ' ||
        grid[i][j + 1] == ' ')
    {
        exit_error("Map validation error", "Open space detected around walkable tile", NULL);
    }
}