/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:00:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/16 21:07:59 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	count_tokens(char **tokens)
{
	int	count;

	count = 0;
	if (!tokens)
		return (0);
	while (tokens[count])
		count++;
	return (count);
}

static int	is_all_digits(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static t_color	*get_target_color(char *id, t_config *config)
{
	if (!ft_strncmp(id, "F", 1))
		return (&config->floor_color);
	else if (!ft_strncmp(id, "C", 1))
		return (&config->ceiling_color);
	return (NULL);
}

int	is_valid_rgb(char **rgb, int *r, int *g, int *b)
{
    char	*r_str;
    char	*g_str;
    char	*b_str;

    r_str = trim_spaces(rgb[0]);
    g_str = trim_spaces(rgb[1]);
    b_str = trim_spaces(rgb[2]);
    if (!r_str || !g_str || !b_str)
        exit_error("Color error", "RGB format is invalid", NULL);
    if (!is_all_digits(r_str) || !is_all_digits(g_str) || !is_all_digits(b_str))
        exit_error("Color error", "RGB values must be digits only", NULL);
    if (ft_strlen(r_str) > 3 || ft_strlen(g_str) > 3 || ft_strlen(b_str) > 3)
        exit_error("Color error", "RGB values must be at most 3 digits", NULL);
    *r = ft_atoi(r_str);
    *g = ft_atoi(g_str);
    *b = ft_atoi(b_str);
    free(r_str);
    free(g_str);
    free(b_str);
    if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
        exit_error("Color error", "RGB value out of range (0-255)", NULL);
    return (1);
}

int	parse_color(char **tokens, t_config *config)
{
    t_color	*color;
    char	**rgb;
    int		rgb_vals[3];

    if (!tokens || !*tokens || !tokens[1])
        return (ERROR);
    if (validate_and_extract_rgb(tokens, &rgb, rgb_vals) == ERROR)
        return (ERROR);
    color = get_target_color(tokens[0], config);
    if (!color || color->is_set)
        return (ft_free_array(rgb), ERROR);
    color->r = rgb_vals[0];
    color->g = rgb_vals[1];
    color->b = rgb_vals[2];
    color->combined = (color->r << 16) | (color->g << 8) | color->b;
    color->is_set = 1;
    ft_free_array(rgb);
    if (tokens[0][0] == 'F')
        config->elements_found |= FLOOR;
    else if (tokens[0][0] == 'C')
        config->elements_found |= CEILING;
    else
        return (ERROR);
    return (SUCCESS);
}
