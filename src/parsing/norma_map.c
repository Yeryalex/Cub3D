/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norma_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:56:31 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/28 09:57:02 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	get_max_width(char **map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

char	**normalize_map(char **map, int *height, int *width)
{
	char	**normalized;
	int		i;
	int		len;

	*height = 0;
	*width = get_max_width(map);
	while (map[*height])
		(*height)++;
	normalized = malloc(sizeof(char *) * (*height + 1));
	if (!normalized)
		exit_error("Memory error", "Failed malloc normalize_map", NULL);
	i = 0;
	while (i < *height)
	{
		len = ft_strlen(map[i]);
		normalized[i] = ft_calloc(*width + 1, sizeof(char));
		if (!normalized[i])
			exit_error("Memory error", "Failed calloc normalize_map row", NULL);
		ft_memset(normalized[i], ' ', *width);
		ft_memcpy(normalized[i], map[i], len);
		i++;
	}
	normalized[i] = NULL;
	return (normalized);
}