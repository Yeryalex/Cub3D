/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:41:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/02 11:17:08 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	transfer_config_to_vars(t_config *config, t_mlx_vars *vars)
{
    if (!config || !vars)
        return ;
    /* copiar resolucion (todavia no se si se customiza o darle una base)*/
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
            free(config->map.grid[i]);
			i++;
		}
		free(config->map.grid);
        config->map.grid = NULL;
    }
}

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}


int	is_empty_line(char *line)
{
    int	i;

    if (!line)
        return (1);
    i = 0;
    while (line[i])
    {
        if (!ft_isspace(line[i]))
            return (0);
        i++;
    }
    return (1);
}
int	is_config_identifier(char *token)
{
    const char	*identifiers[] = {"R", "NO", "SO", "WE", "EA", "F", "C", NULL};
    int			i;

    if (!token)
        return (0);
    i = 0;
    while (identifiers[i])
    {
        if (ft_strncmp(token, identifiers[i], ft_strlen(token)) == 0)
            return (1);
        i++;
    }
    return (0);
}
void	free_split(char **tokens)
{
    int	i;

    if (!tokens)
        return ;
    i = 0;
    while (tokens[i])
    {
        free(tokens[i]); 
        i++;
    }
    free(tokens);
}