/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:06:30 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/07/09 19:34:46 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
		return (-2);
	tokens = ft_split(trimmed_line, ' ');
	if (!tokens)
	{
		free(trimmed_line);
		return (-3);
	}
	result = handle_config_or_map_start(tokens,
			trimmed_line, config, map_started);
	if (result != -1)
		return (free_split(tokens), free(trimmed_line), result);
	result = handle_map_processing(line, trimmed_line, map_started);
	return (free_split(tokens), free(trimmed_line), result);
}

static void	handle_error_result(int result, char *line, t_config *config)
{
	free(line);
	gnl_cleanup();
	if (result == ERROR)
		exit_error_parsing("Config error",
			"Invalid configuration line", config);
	else if (result == -2)
		exit_error_parsing("Memory error", "strtrim failed", config);
	else if (result == -3)
		exit_error_parsing("Memory error", "ft_split failed", config);
	else
		exit_error_parsing("Map error", "Invalid line in map", config);
}

static int	handle_map_line_result(int result, char *line,
		t_config *config, int *map_line_index)
{
	if (result == MAP_LINE)
	{
		if (!store_map_line(config, line, *map_line_index))
		{
			free(line);
			gnl_cleanup();
			exit_error_parsing("Map error", "Invalid map line", config);
		}
		(*map_line_index)++;
		return (1);
	}
	return (0);
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
		if (result < 0 || result == ERROR)
			handle_error_result(result, line, config);
		if (handle_map_line_result(result, line, config, &map_line_index))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		line = get_next_line(fd);
	}
	gnl_cleanup();
	return (map_line_index);
}
