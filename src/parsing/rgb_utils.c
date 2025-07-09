/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:27:27 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/07/09 19:42:57 by rbuitrag         ###   ########.fr       */
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

int	is_all_digits(char *str)
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
