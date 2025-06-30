/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:27:27 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/30 20:32:14 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	extract_rgb_values(char **rgb, int *r, int *g, int *b)
{
	if (!is_valid_rgb(rgb, r, g, b))
		return (ERROR);
	return (SUCCESS);
}

int	validate_and_extract_rgb(char **tokens, char **rgb, int *r)
{
	int		g;
	int		b;
	char	**rgbtest;

	(void)rgb;
	rgbtest = ft_split(tokens[1], ',');
	if (!rgbtest || !(rgbtest)[0] || !(rgbtest)[1] || !(rgbtest)[2]
		|| count_tokens(rgbtest) != 3)
	{
		ft_free_array(rgbtest);
		return (ERROR);
	}
	if (extract_rgb_values(rgbtest, r, &g, &b) == ERROR)
	{
		ft_free_array(rgbtest);
		return (ERROR);
	}
	r[1] = g;
	r[2] = b;
	ft_free_array(rgbtest);
	return (SUCCESS);
}