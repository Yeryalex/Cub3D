/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texcolor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:45:24 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/22 09:22:51 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int parse_texture(char **tokens, t_config *config)
{
    if (ft_strlen(tokens) != 1)
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

    if (!ft_isdigit(r_str) || !ft_isdigit(g_str) || !ft_isdigit(b_str))
        return (0);
	if (ft_strlen(r_str) > 3 || ft_strlen(g_str) > 3 || ft_strlen(b_str) > 3)
		return (0);
	r = ft_atoi(r_str);
    g = ft_atoi(g_str);
    b = ft_atoi(b_str);
    /* Verifica el rango 0-255 */
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (0);
    return (1);
}

int parse_color(char **tokens, t_config *config)
{
	t_color	*color;
	
    if (ft_strlen(tokens) != 3 || !is_valid_rgb(tokens[0], tokens[1], tokens[2]))
        return (ERROR);
	
	if (tokens[0] == 'F')
        color = &config->floor_color;
    else
        color = &config->ceiling_color;
    
    color->r = ft_atoi(tokens[0]);
    color->g = ft_atoi(tokens[1]);
    color->b = ft_atoi(tokens[2]);
    color->combined = (color->r << 16) | (color->g << 8) | color->b;
    color->is_set = 1;
    return (SUCCESS);
}