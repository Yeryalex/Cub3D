/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:12:51 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/16 21:12:51 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	extract_rgb_values(char **rgb, int *r, int *g, int *b)
{
    if (!is_valid_rgb(rgb, r, g, b))
        return (ERROR);
    return (SUCCESS);
}

int	validate_and_extract_rgb(char **tokens, char ***rgb, int *r)
{
    int	g;
    int	b;

    *rgb = ft_split(tokens[1], ',');
    if (!*rgb || !(*rgb)[0] || !(*rgb)[1] || !(*rgb)[2]
        || count_tokens(*rgb) != 3)
    {
        ft_free_array(*rgb);
        exit_error("Color error", "RGB format: three values separated by commas", NULL);
    }
    if (extract_rgb_values(*rgb, r, &g, &b) == ERROR)
    {
        ft_free_array(*rgb);
        return (ERROR);
    }
    r[1] = g;
    r[2] = b;
    return (SUCCESS);
}