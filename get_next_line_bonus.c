/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlamiel- <xlamiel-@student.42barcelona.com>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:08:05 by xlamiel-          #+#    #+#             */
/*   Updated: 2025/06/22 22:33:43 by xlamiel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free_and_null(char **prt)
{
	if (*prt)
	{
		free(*prt);
		*prt = NULL;
	}
	return (NULL);
}

char	*ft_extract_line(char **storage)
{
	char	*line;
	char	*newline_pos;
	char	*temp_storage;

	if (!*storage)
		return (NULL);
	newline_pos = ft_strchr(*storage, '\n');
	if (newline_pos)
	{
		line = ft_substr(*storage, 0, newline_pos - *storage + 1);
		if (!line)
			return (ft_free_and_null(storage));
		temp_storage = ft_strdup(newline_pos + 1);
		ft_free_and_null(storage);
		*storage = temp_storage;
		return (line);
	}
	line = ft_strdup(*storage);
	ft_free_and_null(storage);
	return (line);
}

int	ft_append_read_buffer(char **storage, const char *buffer)
{
	char	*temp;

	if (*storage == NULL)
		temp = ft_strjoin("", buffer);
	else
		temp = ft_strjoin(*storage, buffer);
	if (!temp)
		return (0);
	ft_free_and_null(storage);
	*storage = temp;
	return (1);
}

int	ft_loop_until_newline(int fd, char **storage, char *buffer)
{
	int		bytes_read;

	bytes_read = 1;
	while ((*storage == NULL || !ft_strchr(*storage, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		buffer[bytes_read] = '\0';
		if (!ft_append_read_buffer(storage, buffer))
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*buffer;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free_and_null(&storage[fd]));
	if (!ft_loop_until_newline(fd, &storage[fd], buffer))
	{
		ft_free_and_null(&buffer);
		return (ft_free_and_null(&storage[fd]));
	}
	ft_free_and_null(&buffer);
	if (!storage[fd] || !*storage[fd])
		return (ft_free_and_null(&storage[fd]));
	return (ft_extract_line(&storage[fd]));
}
