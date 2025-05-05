/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texcolor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:45:24 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/05 11:32:20 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Función para contar elementos en un array de strings asi guardo los valores*/
static int count_tokens(char **tokens)
{
    int count = 0;

    if (!tokens)
        return (0);
    while (tokens[count])
        count++;
    return (count);
}

int parse_texture(char **tokens, t_config *config)
{
    char *target_path;
    
    
    if (count_tokens(tokens) != 1)
        return (ERROR);
    if (access(tokens[0], F_OK) != 0)
        return (ERROR);
    target_path = ft_strdup(tokens[1]);
    if (!target_path)
        return (ERROR);
    if (ft_strncmp(tokens[0], "NO", 2) == 0)
        config->north_tex.path = target_path;
    else if (ft_strncmp(tokens[0], "SO", 2) == 0)
        config->south_tex.path = target_path;
    else if (ft_strncmp(tokens[0], "WE", 2) == 0)
        config->west_tex.path = target_path;
    else if (ft_strncmp(tokens[0], "EA", 2) == 0)
        config->east_tex.path = target_path;
    if (ft_strncmp(tokens[0], "NO", 2) == 0)
        config->elements_found |= NORTH;
    else if (ft_strncmp(tokens[0], "SO", 2) == 0)
        config->elements_found |= SOUTH;
    else if (ft_strncmp(tokens[0], "WE", 2) == 0)
        config->elements_found |= WEST;
    else if (ft_strncmp(tokens[0], "EA", 2) == 0)
        config->elements_found |= EAST;
    return (SUCCESS);
}

static int is_valid_rgb(char *r_str, char *g_str, char *b_str)
{
    int r;
    int g;
    int b;
    int i;

    i = 0;
    while(r_str[i])
    {
        if (!ft_isdigit(r_str[i]))
            return (0);
        i++;
    }
    i = 0;
    while (g_str[i])
    {
        if (!ft_isdigit(g_str[i]))
            return (0);
        i++;
    }
    while (b_str[i])
    {
        if (!ft_isdigit(b_str[i]))
            return (0);
        i++;
    }
    if (ft_strlen(r_str) > 3 || ft_strlen(g_str) > 3 || ft_strlen(b_str) > 3)
        return (0);
    r = ft_atoi(r_str);
    g = ft_atoi(g_str);
    b = ft_atoi(b_str);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (0);
    return (1);
}

int parse_color(char **tokens, t_config *config)
{
    t_color *color;

    if (count_tokens(tokens) != 4 || !is_valid_rgb(tokens[1], tokens[2], tokens[3]))
        return (ERROR);

    if (tokens[0][0] == 'F')
        color = &config->floor_color;
    else if (tokens[0][0] == 'C')
        color = &config->ceiling_color;
    else
        return (ERROR);
    if (color->is_set)
        return (ERROR);
    color->r = ft_atoi(tokens[1]);
    color->g = ft_atoi(tokens[2]);
    color->b = ft_atoi(tokens[3]);
    color->combined = (color->r << 16) | (color->g << 8) | color->b;
    color->is_set = 1;
    if (tokens[0][0] == 'F')
        config->elements_found |= FLOOR;
    else if (tokens[0][0] == 'C')
        config->elements_found |= CEILING;
    else
        return (ERROR);
    return (SUCCESS);
}