/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 11:26:36 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/28 11:27:50 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_get_newl_ptr(const char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != '\n')
		++str;
	if (*str)
		return ((char *)str);
	return (NULL);
}