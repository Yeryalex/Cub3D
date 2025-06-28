/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbuitrag <rbuitrag@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 13:12:32 by rbuitrag          #+#    #+#             */
/*   Updated: 2025/06/28 11:30:48 by rbuitrag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>


/*char	*multiple_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*fd_lector(int fd, char *buff, char *saved_text)
{
	ssize_t	bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
			return (multiple_free(&saved_text));
		if (bytes == 0)
			return (saved_text);
		buff[bytes] = '\0';
		if (!saved_text)
			saved_text = ft_strdup("");
		if (!saved_text)
			return (multiple_free(&saved_text));
		temp = saved_text;
		saved_text = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr(buff, '\n'))
			return (saved_text);
	}
	return (saved_text);
}

static char	*ft_line_remover(char *line)
{
	size_t	count;
	char	*saved_text;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (0);
	saved_text = ft_substr(line, count + 1, ft_strlen(line) - (count + 1));
	if (!saved_text)
		return (multiple_free(&saved_text));
	if (*saved_text == '\0')
	{
		free(saved_text);
		saved_text = NULL;
	}
	line[count + 1] = '\0';
	return (saved_text);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*saved_text;
	char		*line;
	char		*tmp;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	line = fd_lector(fd, buff, saved_text);
	free(buff);
	buff = NULL;
	if (!line)
	{
		saved_text = NULL;
		return (NULL);
	}
	saved_text = ft_line_remover(line);
	tmp = ft_strdup(line);
	free(line);
	line = tmp;
	if (!line)
		return (multiple_free(&saved_text));
	return (line);
}*/

#include "get_next_line.h"

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		++len;
	return (len);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	size_t	total_len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!joined)
		return (NULL);
	i = -1;
	while (s1[++i])
		joined[i] = s1[i];
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}

static void	ft_move_buf_content(char *src_buf, char *dst_buf)
{
	int	pos;

	pos = -1;
	while (src_buf[++pos])
	{
		dst_buf[pos] = src_buf[pos];
		src_buf[pos] = '\0';
	}
	while (pos <= BUFFER_SIZE)
		dst_buf[pos++] = '\0';
}

static int	ft_read_file(char **line, int fd)
{
	char	*read_buf;
	char	*joined_buf;
	int		bytes_read;
	int		pos;

	read_buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!read_buf)
	{
		free (*line);
		return (-1);
	}
	pos = 0;
	while (pos <= BUFFER_SIZE)
		read_buf[pos++] = '\0';
	bytes_read = read(fd, read_buf, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		joined_buf = ft_strjoin(*line, read_buf);
		free (*line);
		*line = joined_buf;
		free(joined_buf);
	}
	free (read_buf);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	static_buf[MAX_FD][BUFFER_SIZE];
	char		*line;
	char		*newl_ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	ft_move_buf_content(static_buf[fd], line);
	newl_ptr = ft_get_newl_ptr(line);
	while (!newl_ptr && ft_read_file(&line, fd) > 0)
		newl_ptr = ft_get_newl_ptr(line);
	if (newl_ptr)
		ft_move_buf_content(newl_ptr + 1, static_buf[fd]);
	if (line && !*line)
	{
		free (line);
		line = NULL;
	}
	return (line);
}