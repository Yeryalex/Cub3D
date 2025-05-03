/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:25:02 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/03 11:41:58 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int store_map_line(t_config *config, char *line, int index)
{
    int line_length;

    if (!is_map_line(line))
        return (0);
    line_length = ft_strlen(line);
    if (line_length > config->map.width)
        config->map.width = line_length;
    if (!config->map.grid)
        config->map.grid = (char **)malloc(sizeof(char *) * (config->map.height + 1));
    if (!config->map.grid)
        exit_error("Memory allocation error", "process_map_data", NULL);
    else
        config->map.grid[index] = ft_strdup(line);
    if (!config->map.grid[index])
        exit_error("Memory error", "Failed to allocate memory for map line", NULL);

    return (1);
}

int is_map_line(char *line)
{
    int i;

    if (!line)
        return (0);
    i = 0;
    while (line[i])
	{
		if (!ft_strchr(" 01NSEW", line[i]))
			return (0);
        i++;
    }
    return (1);
}

int add_map_line(char *line)
{
    char    *trimmed;
    
	printf("Adding map line: %s", line); // control map line
    trimmed = ft_strtrim(line, " \t");
    if (!trimmed)
        exit_error("Memory error", "strtrim failed", NULL);
    return (SUCCESS);
}
