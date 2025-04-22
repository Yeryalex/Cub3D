/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:50:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/16 10:18:31 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

void	process_map_data(t_list **map_list, t_config *config)
{
    t_list	*current;
    int		i;

    if (!map_list || !*map_list || !config)
        exit_error("Processing error", "Invalid map data", NULL);
    config->map.height = ft_lstsize(*map_list);
    config->map.grid = (char **)malloc(sizeof(char *) * (config->map.height + 1));
    if (!config->map.grid)
        exit_error("Memory allocation error", "process_map_data", NULL);
    current = *map_list;
    i = 0;
    while (current)
    {
        config->map.grid[i] = ft_strdup((char *)current->content);
        if (!config->map.grid[i])
            exit_error("Memory allocation error", "process_map_data", NULL);
        current = current->next;
        i++;
    }
    config->map.grid[i] = NULL;
    ft_lstclear(map_list, free);
    validate_map(config->map.grid, config);
}