/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:07 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/05 18:34:33 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


static int	parse_config_line(char **tokens, t_config *config)
{
	if (tokens == NULL || tokens[0] == NULL)
    	return (free_split(tokens), ERROR);
    if (!ft_strncmp(tokens[0], "NO", 2) || !ft_strncmp(tokens[0], "SO", 2)\
     || !ft_strncmp(tokens[0], "WE", 2) || !ft_strncmp(tokens[0], "EA", 2))
    {
        if (!parse_texture(tokens, config))
            return (free_split(tokens), ERROR);
    }
    else if (!ft_strncmp(tokens[0], "F", 1) || !ft_strncmp(tokens[0], "C", 1))
    {
        if (!parse_color(tokens, config))
           return (free_split(tokens), ERROR);
    }
    return (SUCCESS);
}

static int	handle_line(char *line, t_config *config, int *map_started)
{
    char	**tokens;
    char	*trimmed_line;

    if (!line || !config)
    {
        if (!line)
            return (SUCCESS);
        return (ERROR);
    }
    if (is_empty_line(line))
    {
        if (*map_started)
            return (ERROR);
        return (SUCCESS);
    }
    trimmed_line = ft_strtrim(line, "\n");
    if (!trimmed_line)
    {
        free(line);
        exit_error("Memory error", "strtrim failed", NULL);
    }
    tokens = ft_split(trimmed_line, ' ');
    if (!tokens)
    {
        free(trimmed_line);
        free(line);
        exit_error("Memory error", "ft_split failed", NULL);
    }
    if (!*map_started && is_config_identifier(tokens[0]))
    {
        if (!parse_config_line(tokens, config))
        {
            free_split(tokens);
            free(trimmed_line);
            return (ERROR);
        }
        free_split(tokens);
        free(trimmed_line);
        return (SUCCESS);
    }
    else if (!*map_started && is_map_line(trimmed_line))
    {
        *map_started = 1;
        free_split(tokens);
        free(trimmed_line);
        return (MAP_LINE);
    }
    if (*map_started)
    {
        if (is_empty_line(line))
        {
            free_split(tokens);
            free(trimmed_line);
            return (ERROR);
        }
        if (is_map_line(trimmed_line))
        {
            *map_started = 1;
            free_split(tokens);
            free(trimmed_line);
            return (MAP_LINE);
        }
        free_split(tokens);
        free(trimmed_line);
        exit_error("Map error", "No map found in scene file", NULL);
    }
    free_split(tokens);
    free(trimmed_line);
    return (SUCCESS);
}

static int process_file_lines(t_config *config, int fd)
{
    char    *line;
    int     map_line_index;
    int     result;
    int     map_started;

    map_line_index = 0;
    map_started = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        result = handle_line(line, config, &map_started);
        if (result == ERROR)
        {
            free(line);
            exit_error("Config error", "Invalid configuration line", NULL);
        }
        else if (result == MAP_LINE)
        {
            
            if (!store_map_line(config, line, map_line_index))
            {
                free(line);
                exit_error("Map error", "Invalid map line", NULL);
            }
            map_line_index = map_line_index + 1;
        }
        else if (result == SUCCESS)
        {
            free(line);
            continue;
        }
        else
        {
            free(line);
            exit_error("Map error", "Invalid line in map", NULL);
        }
        free(line);
    }
    return (map_line_index);
}

int	parse_scene_file(char *filename, t_config *config)
{
	int		fd;
	int		dir_fd;
	
	if (!ft_strnstr(filename, ".cub", ft_strlen(filename)) || 
        ft_strlen(filename) < 5) 
            exit_error("File error ", "Invalid file extension. Expected .cub\n", NULL);
	dir_fd = open(filename, O_DIRECTORY);
	if (dir_fd >= 0)
	{
		close(dir_fd);
		exit_error("File error: ", "Provided path is a directory, not a file\n", NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("File open error: ", filename, NULL);
    config->map.height = process_file_lines(config, fd);
	close(fd);
    return (SUCCESS);
}
int	parser_scene(char **av, t_mlx_vars *vars)
{
	t_config	config;

    init_config(&config);
   
    if (parse_scene_file(av[1], &config) == ERROR)
		exit_error("Scene parsing failed", av[1], vars);
    validate_map(&config);
    validate_scene_elements(&config);
    transfer_config_to_vars(&config, vars);
   	return (0);
}