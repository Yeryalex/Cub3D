/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:06:30 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/12 20:35:28 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	handle_config_or_map_start(
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

static int	handle_map_processing(char *line,
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
		exit_error("Map error", "No map found in scene file", NULL);
	}
	return (SUCCESS);
}

static int	handle_line(char *line, t_config *config, int *map_started)
{
	char	**tokens;
	char	*trimmed_line;
	int		result;

	if (!line || !config)
		return (ERROR);
	if (is_empty_line(line) && !*map_started)
		return (SUCCESS);
	if (is_empty_line(line))
		return (ERROR);
	trimmed_line = ft_strtrim(line, "\n");
	if (!trimmed_line)
		exit_error("Memory error", "strtrim failed", NULL);
	tokens = ft_split(trimmed_line, ' ');
	if (!tokens)
		exit_error("Memory error", "ft_split failed", NULL);
	result = handle_config_or_map_start(tokens,
			trimmed_line, config, map_started);
	if (result != -1)
		return (free_split(tokens), free(trimmed_line), result);
	result = handle_map_processing(line, trimmed_line, map_started);
	return (free_split(tokens), free(trimmed_line), result);
}

static void	handle_result(int result, t_config *config,
	char *line, int *map_index)
{
	if (result == ERROR)
		exit_error("Config error", "Invalid configuration line", NULL);
	else if (result == MAP_LINE)
	{
		if (!store_map_line(config, line, *map_index))
			exit_error("Map error", "Invalid map line", NULL);
		*map_index = *map_index + 1;
	}
	else if (result != SUCCESS)
		exit_error("Map error", "Invalid line in map", NULL);
}

int	process_file_lines(t_config *config, int fd)
{
	char	*line;
	int		map_line_index;
	int		result;
	int		map_started;

	map_line_index = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		result = handle_line(line, config, &map_started);
		handle_result(result, config, line, &map_line_index);
		free(line);
		line = get_next_line(fd);
	}
	return (map_line_index);
}
