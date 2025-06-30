/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:00:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/30 20:04:02 by rbuitrag         ###   ########.fr       */
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
	if (!is_all_digits(rgb[0]) || !is_all_digits(rgb[1]) || !is_all_digits(rgb[2]))
		return (0);
	if (ft_strlen(rgb[0]) > 3 || ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 3)
		return (0);
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

int	parse_color(char **tokens, t_config *config)
{
	t_color	*color;
	int		rgb_vals[3];

	if (!tokens || !*tokens || !tokens[1])
		return (ERROR);
	color = get_target_color(tokens[0], config);
	if (!color || color->is_set)
		return (ERROR);
	if (validate_and_extract_rgb(tokens, NULL, rgb_vals) == ERROR)
		return (ERROR);
	color->r = rgb_vals[0];
	color->g = rgb_vals[1];
	color->b = rgb_vals[2];
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
