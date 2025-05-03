/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:28:07 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/03 20:02:03 by rbuitrag         ###   ########.fr       */
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

static int handle_line(char *line, t_config *config, int map_started)
{
    char **tokens;
    
    if (!line || !config)
        return (ERROR);
    printf("Processing line: %s", line);
    if (is_empty_line(line))
    {
        if (map_started)
            return (ERROR);
        return (SUCCESS);
    } 
    tokens = ft_split(line, ' '); // Revisar Mejor que split(' ') para manejar múltiples espacios
    if (!tokens)
        exit_error("Memory error", "ft_split failed", NULL);
    if (map_started == 0 && is_config_identifier(tokens[0]))
    {
        if (parse_config_line(tokens, config) == ERROR)
            return (free_split(tokens), ERROR);
    }
    else if (map_started == 1)
    {
        if (is_empty_line(line))
            return (free_split(tokens), ERROR);
        if (is_map_line(tokens[0]))
            return (free_split(tokens), MAP_LINE);
        else
            return (free_split(tokens), ERROR);
    }
    return (SUCCESS);
}

static int process_file_lines(t_config *config, int fd)
{
    char    *line;
    int     map_started;
    int     map_line_index;
    int     result;

    map_started = 0;
    map_line_index = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        result = handle_line(line, config, map_started);
        if (result == ERROR)
        {
            free(line);
            exit_error("Config error", "Invalid configuration line", NULL);
        }
        else if (result == MAP_LINE)
        {
            map_started = 1;
            map_line_index = map_line_index + 1; // Incrementar el indice del mapa
            printf ("sumando lineas de escenario ahora es: %d\n", map_line_index);
            if (!store_map_line(config, line, map_line_index))
            {
                free(line);
                exit_error("Map error", "Invalid map line", NULL);
            }
        }
        free(line);
    }
    if (map_started)
        exit_error("Map error", "No map found in scene file", NULL);
    return (map_line_index);
}

int	parse_scene_file(char *filename, t_config *config)
{
	int		fd;
	int		dir_fd;
	
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
    config->map.height = process_file_lines(config, fd);
	close(fd);
    printf ("LLegamos a antes de validar los elementos del mapa->config\n");
    printf ("Resolution width: %d\n", config->win_width);
    printf ("Resolution width: %d\n", config->win_height);
    printf ("Resolution ok es: %d\n", config->res_set);
    printf ("Ancho del mapa valor max dibujado: %d\n", config->map.width);
    printf ("Alto del mapa num lineas leidas de escenario: %d\n", config->map.height);
    return (SUCCESS);
}
int	parser_scene(char **av, t_mlx_vars *vars)
{
	t_config	config;

    init_config(&config);
    if (parse_scene_file(av[1], &config) == ERROR)
		exit_error("Scene parsing failed", av[1], vars);
    printf ("Validado lo pasamos a la estructura config\n");
    validate_map(&config);
    printf ("Lo hemos validado elementos, procesamos mapa para config\n");
    validate_scene_elements(&config);
	transfer_config_to_vars(&config, vars);
    return (0);
}