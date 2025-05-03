/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:41:44 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/05/03 09:17:04 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}


int	is_empty_line(char *line)
{
    int	i;

    if (!line)
        return (1);
    i = 0;
    while (line[i])
    {
        if (!ft_isspace(line[i]))
            return (0);
        i++;
    }
    return (1);
}
int	is_config_identifier(char *token)
{
    const char	*identifiers[] = {"R", "NO", "SO", "WE", "EA", "F", "C", NULL};
    int			i;

    if (!token)
        return (0);
    i = 0;
    while (identifiers[i])
    {
        if (ft_strncmp(token, identifiers[i], ft_strlen(token)) == 0)
            return (1);
        i++;
    }
    return (0);
}
void	free_split(char **tokens)
{
    int	i;

    if (!tokens)
        return ;
    i = 0;
    while (tokens[i])
    {
        free(tokens[i]); 
        i++;
    }
    free(tokens);
}