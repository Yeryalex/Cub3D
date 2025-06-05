/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:50:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/05 18:35:50 by rbuitrag         ###   ########.fr       */
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