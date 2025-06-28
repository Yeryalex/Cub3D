/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:25:02 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/28 10:13:36 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
		exit_error("Memory error", "strtrim failed", NULL);
	}
	line_length = ft_strlen(line_trimmed);
	if (line_length > config->map.width)
		config->map.width = line_length;
	config->map.grid[index] = ft_strdup(line_trimmed);
	if (!config->map.grid[index])
	{
		free(line);
		free(line_trimmed);
		exit_error("Memory error", "Failed memory for map line", NULL);
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
		exit_error("Memory error", "strtrim failed", NULL);
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
        exit_error("Memory error", "failed in trim_spaces", NULL);
    return (trimmed);
}