/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:07 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/30 13:28:22 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	parse_config_line(char **tokens, t_config *c)
{
	const t_parser parsers[] = {
        {"NO", parse_texture}, {"SO", parse_texture},
        {"WE", parse_texture}, {"EA", parse_texture},
        {"F", parse_color},    {"C", parse_color},
        {NULL, NULL},
    };
	int				i;

	i = -1;
	if (tokens == NULL || tokens[0] == NULL)
    	return (ERROR);
	while (parsers[++i].id)
	{
		if (ft_strncmp(tokens[0], parsers[i].id, ft_strlen (tokens[0])) == 0)
		{
			parsers[i].func(tokens, c);
			free_split(tokens);
			return (SUCCESS);
		}
	}
	free_split(tokens);
	return (ERROR);
}

static int handle_line(char *line, t_config *c, int *map_started, t_list **ml)
{
    char **tokens;

    if (!line || !c || !ml)
        return (ERROR);
    tokens = ft_split(line, ' '); // Manejar múltiples espacios
    if (!tokens)
        exit_error("Memory error", "ft_split failed", NULL);
    if (!*map_started && is_config_identifier(tokens[0]))
    {
        if (parse_config_line(tokens, c) == ERROR)
            return (free_split(tokens), ERROR);
    }
    else
    {
        free_split(tokens);
        return (ERROR);
    }
    if (is_empty_line(line))
    {
        if (*map_started)
            return (ERROR);
        return (SUCCESS);
    }
    if (*map_started || is_map_line(line))
    {
        *map_started = 1;
        if (add_map_line(line, ml) == ERROR)
            return (ERROR);
        return (SUCCESS);
    }
    free_split(tokens);
    return (SUCCESS);
}

static char	*process_file_lines(t_config *c, t_list **map_list, int fd)
{
    char	*line;
    int		map_started;

    map_started = 0;
    printf ("Fd valor antes de gnl: %d\n", fd);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line map: %s\n", line);
        if (handle_line(line, c, &map_started, map_list) == ERROR)
        {
            free(line);
            ft_lstclear(map_list, free);
            exit_error("Invalid line in scene file:", line, NULL);
        }
        free(line);
    }
    if (line == NULL)
    {
        free(line);
        ft_lstclear(map_list, free);
        exit_error("File read error", "get_next_line failed", NULL);
	}
    if (!map_started) // Si no se encontró un mapa, es un error
    {
        free(line);
        ft_lstclear(map_list, free);
        exit_error("Map error", "No map found in scene file", NULL);
    }
	return (line);
}

int	parse_scene_file(char *filename, t_config *config)
{
	int		fd;
	int		dir_fd;
	t_list	*map_list;

	if (!ft_strnstr(filename, ".cub", ft_strlen(filename)) || 
        ft_strlen(filename) < 5) 
        //ft_strncmp(filename, ".cub", ft_strlen(filename) != 0))
        exit_error("File error ", "Invalid file extension. Expected .cub", NULL);
	dir_fd = open(filename, O_DIRECTORY);
	if (dir_fd >= 0)
	{
		close(dir_fd);
		exit_error("File error ", "Provided path is a directory, not a file", NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("File open error: ", filename, NULL);
	map_list = NULL;
    process_file_lines(config, &map_list, fd);
	close(fd);
	validate_scene_elements(config);
	process_map_data(&map_list, config);
	return (SUCCESS);
}
int	parser_scene(char **av, t_mlx_vars *vars)
{
	t_config	config;

	ft_memset(&config, 0, sizeof(t_config));
	if (parse_scene_file(av[1], &config) == ERROR)
		exit_error("Scene parsing failed", av[1], vars);
	transfer_config_to_vars(&config, vars);
	free_config(&config);
	return (0);
}