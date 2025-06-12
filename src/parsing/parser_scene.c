/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:07 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/12 20:21:38 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	parse_config_line(char **tokens, t_config *config)
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

int parser_scene(char **av, t_mlx_vars *vars)
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