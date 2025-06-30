/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:25:02 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/30 20:57:40 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	normalize_map_lines(t_config *config)
{
	int		i;
	int		current_len;
	char	*normalized_line;
	char	*old_line;

	i = 0;
	while (i < config->map.height)
	{
		current_len = ft_strlen(config->map.grid[i]);
		if (current_len < config->map.width)
		{
			normalized_line = malloc(config->map.width + 1);
			if (!normalized_line)
				exit_error_parsing("Memory error", "Failed to normalize map line", config);
			ft_memcpy(normalized_line, config->map.grid[i], current_len);
			ft_memset(normalized_line + current_len, ' ', config->map.width - current_len);
			normalized_line[config->map.width] = '\0';
			old_line = config->map.grid[i];
			config->map.grid[i] = normalized_line;
			free(old_line);
		}
		i++;
	}
}

int	store_map_line(t_config *config, char *line, int index)
{
	int		line_length;
	char	*line_trimmed;

	if (!config || !line || !config->map.grid)
		return (0);
	line_trimmed = ft_strtrim(line, "\n");
	if (!line_trimmed)
	{
		free(line);
		exit_error_parsing("Memory error", "strtrim failed", config);
	}
	line_length = ft_strlen(line_trimmed);
	if (line_length > config->map.width)
		config->map.width = line_length;
	config->map.grid[index] = ft_strdup(line_trimmed);
	if (!config->map.grid[index])
	{
		free(line);
		free(line_trimmed);
		exit_error_parsing("Memory error", "Failed memory for map line", config);
	}
	free(line_trimmed);
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr(" 01NSEW", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	add_map_line(char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (ERROR);
	free(trimmed);
	return (SUCCESS);
}
char	*trim_spaces(char *str)
{
	int		start;
	int		end;
	char	*trimmed;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'))
		start++;
	end = ft_strlen(str) - 1;
	while (end >= start && (str[end] == ' ' || str[end] == '\t'))
		end--;
	trimmed = ft_substr(str, start, end - start + 1);
	if (!trimmed)
		return (NULL);
	return (trimmed);
}
