/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 09:16:17 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/06 12:16:30 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void init_config(t_config *config)
{
    ft_bzero(config, sizeof(t_config));
    config->win_width = RES_WINWIDHT;
    config->win_height = RES_WINHEIGHT;
    config->res_set = 1;
    config->map.grid = malloc(sizeof(char *) * MAX_MAP_HEIGHT + 1); // Asignar memoria para el grid
    if (!config->map.grid)
    exit_error("Memory error", "Failed to allocate memory for map grid", NULL);
    config->map.width = 0;
    config->map.height = 0;
}

void	transfer_config_to_vars(t_config *config, t_mlx_vars *vars)
{
    if (!config || !vars)
        return ;
    /* Puedo cambiarla en el define de cub3d.h*/
    vars->config.win_width = config->win_width;
    vars->config.win_height = config->win_height;
    vars->config.res_set = config->res_set;
    /* Copiar texturas */
    vars->config.north_tex.path = ft_strdup(config->north_tex.path);
    vars->config.south_tex.path = ft_strdup(config->south_tex.path);
    vars->config.east_tex.path = ft_strdup(config->east_tex.path);
    vars->config.west_tex.path = ft_strdup(config->west_tex.path);
    /* Copiar colores */
    vars->config.floor_color = config->floor_color;
    vars->config.ceiling_color = config->ceiling_color;
    if (!vars->config.north_tex.path || !vars->config.south_tex.path
        || !vars->config.east_tex.path || !vars->config.west_tex.path)
        exit_error("Memory allocation error", "transfer_config_to_vars", vars);
}

void	free_config(t_config *config)
{
	int	i;
    
    if (!config)
       return ;
    free(config->north_tex.path);
    free(config->south_tex.path);
    free(config->east_tex.path);
    free(config->west_tex.path);
    config->north_tex.path = NULL;
    config->south_tex.path = NULL;
    config->east_tex.path = NULL;
    config->west_tex.path = NULL;
	/* Si hay mapa do it */
	if (config->map.grid)
    {
		i = 0;
        while (config->map.grid[i])
		{
            free(&config->map.grid[i]);
			i++;
		}
		free(config->map.grid);
        config->map.grid = NULL;
    }
}