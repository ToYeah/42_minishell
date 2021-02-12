/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 21:34:07 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/12 20:16:42 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static int	append_line(char **line, const char *src)
{
	size_t	line_len;
	size_t	src_len;
	char	*tmp_line;

	line_len = ft_strlen(*line);
	src_len = ft_strlen(src);
	if (!(tmp_line = ft_strdup(*line)))
	{
		return (0);
	}
	free(*line);
	*line = (char *)malloc((line_len + src_len + 1) * sizeof(char));
	if (*line == NULL)
	{
		return (0);
	}
	ft_strlcpy(*line, tmp_line, line_len + 1);
	ft_strlcpy(*line + line_len, src, src_len + 1);
	free(tmp_line);
	return (1);
}

void		free_set(char **ptr, char *value)
{
	if (ptr)
	{
		free(*ptr);
		*ptr = value;
	}
}

int			free_and_return(char **line, char **buffer, int return_value)
{
	free_set(line, NULL);
	free_set(buffer, NULL);
	return (return_value);
}

int			read_fd(int fd, char **line, char **fd_buffer, char *buffer)
{
	ssize_t	result;
	char	*newline;

	while ((result = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[result] = '\0';
		if ((newline = ft_strchr(buffer, '\n')) != NULL)
		{
			*newline = '\0';
			if (!append_line(line, buffer))
				return (free_and_return(line, &buffer, STATUS_ERROR));
			if (!(*fd_buffer = ft_strdup(newline + 1)))
				return (free_and_return(line, &buffer, STATUS_ERROR));
			return (free_and_return(NULL, &buffer, STATUS_LINE));
		}
		else
		{
			if (!append_line(line, buffer))
				return (free_and_return(line, &buffer, STATUS_ERROR));
		}
	}
	return (free_and_return(NULL, &buffer, result));
}

int			get_next_line(int fd, char **line)
{
	static char	*fd_buffer;
	char		*buffer;
	char		*tmp;
	char		*newline;

	if (fd < 0 || fd >= FOPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (STATUS_ERROR);
	if (!fd_buffer && !(fd_buffer = ft_strdup("")))
		return (STATUS_ERROR);
	if ((newline = ft_strchr(fd_buffer, '\n')) != NULL)
	{
		*newline = '\0';
		if (!(*line = ft_strdup(fd_buffer)))
			return (STATUS_ERROR);
		if (!(tmp = ft_strdup(newline + 1)))
			return (free_and_return(line, NULL, STATUS_ERROR));
		free_set(&fd_buffer, tmp);
		return (STATUS_LINE);
	}
	if (!(*line = ft_strdup(fd_buffer)))
		return (STATUS_ERROR);
	free_and_return(NULL, &fd_buffer, 0);
	if (!(buffer = (char *)malloc(BUFFER_SIZE + 1)))
		return (free_and_return(line, NULL, STATUS_ERROR));
	return (read_fd(fd, line, &fd_buffer, buffer));
}
