/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:40:18 by rbuitrag          #+#    #+#             */
/*   Updated: 2024/01/31 12:25:59 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (is_set(s1[start], set))
		start++;
	if (start == end)
		return (ft_strdup(""));
	while (is_set(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, end - start));
}
/*
int	main(void)
{
	const char		*s1;
	const char		*set;
	char			*cut;

	s1 = "ABBAperABixcoBBAAB";
	set = "BA";
	printf("La cadena s1 es: %s\n", s1);
	printf("A recortar: %s\n", set);
	cut = ft_strtrim(s1, set);
	printf("La cadena recortada es: %s\n", cut);
	return (0);
}*/
