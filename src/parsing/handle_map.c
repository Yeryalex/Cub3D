/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:31:15 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/07/09 19:31:15 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	handle_config_or_map_start(
	char **tokens, char *trimmed_line, t_config *config, int *map_started)
{
	if (!*map_started && is_config_identifier(tokens[0]))
	{
		if (!parse_config_line(tokens, config))
			return (ERROR);
		return (SUCCESS);
	}
	if (!*map_started && is_map_line(trimmed_line))
	{
		*map_started = 1;
		return (MAP_LINE);
	}
	return (-1);
}

int	handle_map_processing(char *line,
		char *trimmed_line, int *map_started)
{
	if (*map_started)
	{
		if (is_empty_line(line))
			return (ERROR);
		if (is_map_line(trimmed_line))
		{
			*map_started = 1;
			return (MAP_LINE);
		}
		return (ERROR);
	}
	return (SUCCESS);
}
