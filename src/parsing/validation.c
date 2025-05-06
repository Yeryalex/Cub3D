/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:50:19 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/06 09:27:09 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	validate_scene_elements(t_config *config)
{
    if (!config)
        exit_error("Validation error", "Config is NULL", NULL);
    /* [IMPRIMO LAS CONFIGURACIONES QUE HAN LLEGADO HASTA AQUI]*/
    printf ("Textura NORTH: %s\n", config->north_tex.path);
    printf ("Textura South: %s\n", config->south_tex.path);
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