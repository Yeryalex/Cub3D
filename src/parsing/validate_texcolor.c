/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texcolor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:45:24 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/03 09:20:41 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Función para contar elementos en un array de strings asi guardo los valores*/
static int count_tokens(char **tokens)
{
    int count = 0;

    while (tokens[count])
        count++;
    return (count);
}

int parse_texture(char **tokens, t_config *config)
{
    if (count_tokens(tokens) != 1)
        return (ERROR);
    if (!config->north_tex.path)
    {
        config->north_tex.path = ft_strdup(tokens[0]);
        config->elements_found |= NORTH;
        return (SUCCESS);
    }
    return (ERROR); 
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
    color->r = ft_atoi(tokens[1]);
    color->g = ft_atoi(tokens[2]);
    color->b = ft_atoi(tokens[3]);
    color->combined = (color->r << 16) | (color->g << 8) | color->b;
    color->is_set = 1;
    return (SUCCESS);
}