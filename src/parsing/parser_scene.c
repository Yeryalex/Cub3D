/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:07 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/02 13:43:39 by rbuitrag         ###   ########.fr       */
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
    	return (free_split(tokens), ERROR);
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
    printf("Processing line: %s", line);
    if (is_empty_line(line))
    {
        if (*map_started)
            return (ERROR);
        return (SUCCESS);
    } 
    tokens = ft_split(line, ' '); /*  Revisar Mejor que split(' ') para manejar múltiples espacios */
    if (!tokens)
        exit_error("Memory error", "ft_split failed", NULL);
    
    if (!*map_started && is_config_identifier(tokens[0]))
    {
        if (parse_config_line(tokens, c) == ERROR)
            return (free_split(tokens), ERROR);
    }
    else if (*map_started || is_map_line(tokens[0]))
    {
        if (is_map_line(tokens[0]))
            *map_started = 1;
        if (add_map_line(line, ml) == ERROR)
            return (free_split(tokens), ERROR);
    }
    else if (*map_started && is_empty_line(line))
    {
        free_split(tokens);
        return (SUCCESS);
    }
    else if (*map_started && !is_empty_line(line))
    {
        *map_started = 1;
        if (add_map_line(line, ml) == ERROR)
            return (free_split(tokens), ERROR);
            //Aqui debo guardar los valores de personaje/posicion camara
    }
    else
        return (free_split(tokens), ERROR);
    return (SUCCESS);
}

static char *process_file_lines(t_config *c, t_list **map_list, int fd)
{
    char    *line;
    char    *line_copy;
    int     map_started;

    map_started = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        line_copy = ft_strdup(line);
        if (!line_copy)
            exit_error("Memory error", "ft_strdup failed", NULL);
        if (handle_line(line, c, &map_started, map_list) == ERROR)
        {
            free(line);
            ft_lstclear(map_list, free);
            return (NULL);
            //exit_error("Invalid line:", line_copy, NULL);
        }
        free(line_copy);
        free(line);
        c->map.height += 1;
    }
    if (!map_started)
    {
        ft_lstclear(map_list, free);
        exit_error("Map error", "No map found", NULL);
    }
    return (NULL);
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
		exit_error("File error: ", "Provided path is a directory, not a file", NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("File open error: ", filename, NULL);
	map_list = NULL;
    process_file_lines(config, &map_list, fd);
	close(fd);
    printf ("LLegamos a antes de validar los elementos del mapa->config\n");
    printf ("Resolution width: %d\n", config->win_width);
    printf ("Resolution width: %d\n", config->win_height);
    printf ("Resolution ok es: %d\n", config->res_set);
	process_map_data(&map_list, config);
    printf ("Lo hemos validado elementos, procesamos mapa para config\n");
    validate_scene_elements(config);
    return (SUCCESS);
}
int	parser_scene(char **av, t_mlx_vars *vars)
{
	t_config	config;

    ft_memset(&config, 0, sizeof(t_config));
    config.win_width = 1920;
    config.win_height = 1020;
    config.res_set = 1;
	if (parse_scene_file(av[1], &config) == ERROR)
		exit_error("Scene parsing failed", av[1], vars);
    printf ("Validado lo pasamos a la estructura config\n");
	transfer_config_to_vars(&config, vars);
    printf ("Todo guardado lo devolvememos a main\n");
	//free_config(&config);
	return (0);
}