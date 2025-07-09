/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:18:00 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/07/09 20:18:00 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	*get_di_array(void)
{
	static int	di[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

	return (di);
}

static int	*get_dj_array(void)
{
	static int	dj[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

	return (dj);
}

int	check_adjacent_walkable(char **grid, int i, int j, t_config *config)
{
	int	k;
	int	ni;
	int	nj;
	int	height;

	height = config->map.height;
	k = 0;
	while (k < 8)
	{
		ni = i + get_di_array()[k];
		nj = j + get_dj_array()[k];
		if (ni >= 0 && ni < height && nj >= 0 && grid[ni]
			&& nj < (int)ft_strlen(grid[ni]) && (grid[ni][nj] == '0'
			|| grid[ni][nj] == 'N' || grid[ni][nj] == 'S'
			|| grid[ni][nj] == 'E' || grid[ni][nj] == 'W'))
			return (1);
		k++;
	}
	return (0);
}
