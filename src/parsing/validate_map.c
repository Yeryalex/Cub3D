/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:35:26 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/16 11:51:39 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

static void	validate_map_borders(char **grid, int height, int width)
{
    int	i;
    int	j;

    i = 0;
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
    // Validar primera y ultima columna
    i = 0;
    while (i < height)
    {
        if (grid[i][0] != '1' && grid[i][0] != ' ')
            exit_error("Map validation error", "Map is not closed on the left", NULL);
        if (grid[i][width - 1] != '1' && grid[i][width - 1] != ' ')
            exit_error("Map validation error", "Map is not closed on the right", NULL);
        i++;
    }
}

static void	validate_map_content(char **grid, t_config *config)
{
    int	i;
    int	j;

    i = 0;
    while (grid[i])
    {
        j = 0;
        while (grid[i][j])
        {
            if (!is_valid_map_char(grid[i][j]))
                exit_error("Map validation error", "Invalid character in map", NULL);
            if (grid[i][j] == 'N' || grid[i][j] == 'S'
                || grid[i][j] == 'E' || grid[i][j] == 'W')
            {
                if (config->player.found)
                    exit_error("Map validation error", "Multiple players found", NULL);
                config->player.found = 1;
                config->player.start_direction = grid[i][j];
                config->player.pos_x = j + 0.5;
                config->player.pos_y = i + 0.5;
            }
            j++;
        }
        i++;
    }
    if (!config->player.found)
        exit_error("Map validation error", "No player found in map", NULL);
}

void	validate_map(char **grid, t_config *config)
{
    int	height;
    int	width;

    if (!grid || !config)
        exit_error("Map validation error", "Invalid map or config", NULL);
    height = config->map.height;
    width = config->map.width;
    validate_map_borders(grid, height, width);
    validate_map_content(grid, config);
}