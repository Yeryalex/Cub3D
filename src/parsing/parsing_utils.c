/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:25:02 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/04/25 13:59:21 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_map_line(char **tokens)
{
	int	i;
	int	j;

	if (!tokens || !tokens[0])
		return (0);
	i = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
		{
			if (!ft_strchr(" 01NSEW", tokens[i][j]))
			return (0);
			j++;
		}
		i++;
	}
	return (1);
}
int	add_map_line(char *line, t_list **map_list)
{
	char	*trimmed;
	t_list	*new_node;

	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		exit_error("Memory error", "strtrim failed", NULL);
	new_node = ft_lstnew(trimmed);
	if (!new_node)
	{
		free(trimmed);
		exit_error("Memory error", "lstnew failed", NULL);
	}
	ft_lstadd_back(map_list, new_node);
	return (SUCCESS);
}
