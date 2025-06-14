/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 08:45:24 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/14 12:17:42 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_visited(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}

static void	assign_texture_path(char **tokens, t_config *config, char *path)
{
	if (ft_strncmp(tokens[0], "NO", 2) == 0)
		config->north_tex.path = path;
	else if (ft_strncmp(tokens[0], "SO", 2) == 0)
		config->south_tex.path = path;
	else if (ft_strncmp(tokens[0], "WE", 2) == 0)
		config->west_tex.path = path;
	else if (ft_strncmp(tokens[0], "EA", 2) == 0)
		config->east_tex.path = path;
}

static void	set_element_flag(char **tokens, t_config *config)
{
	if (ft_strncmp(tokens[0], "NO", 2) == 0)
		config->elements_found |= NORTH;
	else if (ft_strncmp(tokens[0], "SO", 2) == 0)
		config->elements_found |= SOUTH;
	else if (ft_strncmp(tokens[0], "WE", 2) == 0)
		config->elements_found |= WEST;
	else if (ft_strncmp(tokens[0], "EA", 2) == 0)
		config->elements_found |= EAST;
}

int	parse_texture(char **tokens, t_config *config)
{
	char	*target_path;

	if (count_tokens(tokens) == 1)
		return (ERROR);
	if (access(tokens[1], F_OK) != 0)
		return (ERROR);
	target_path = ft_strdup(tokens[1]);
	if (!target_path)
		return (ERROR);
	assign_texture_path(tokens, config, target_path);
	set_element_flag(tokens, config);
	return (SUCCESS);
}
