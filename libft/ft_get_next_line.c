/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:15:53 by totaisei          #+#    #+#             */
/*   Updated: 2020/12/18 18:58:32 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	free_all(char *storage, char *buf, char *line)
{
	free(buf);
	free(storage);
	free(line);
	return (-1);
}

static int	success_gnl(char *nl_p, char **storage, char *buf, char **line)
{
	char *tmp;

	tmp = NULL;
	*nl_p = '\0';
	if (!(*line = ft_strjoin(*storage, buf)))
		return (free_all(*storage, buf, *line));
	tmp = *storage;
	if (!(*storage = ft_strjoin((nl_p + 1), NULL)))
		return (free_all(tmp, buf, *line));
	ft_safe_free_char(&tmp);
	ft_safe_free_char(&buf);
	return (1);
}

static int	finish_gnl(char **storage, char *buf, char **line)
{
	if (!(*line = ft_strjoin(*storage, buf)))
		return (free_all(*storage, buf, *line));
	ft_safe_free_char(storage);
	ft_safe_free_char(&buf);
	return (0);
}

static int	loop_gnl(int fd, char **storage, char *buf, char **line)
{
	char		*tmp;
	ssize_t		read_len;

	while (1)
	{
		read_len = read(fd, buf, GNL_BUFFER_SIZE);
		if (read_len < 0)
			return (free_all(*storage, buf, *line));
		buf[read_len] = '\0';
		if (read_len < GNL_BUFFER_SIZE)
		{
			if ((tmp = ft_find_new_line(buf, read_len)))
				return (success_gnl(tmp, storage, buf, line));
			else
				return (finish_gnl(storage, buf, line));
		}
		if ((tmp = ft_find_new_line(buf, GNL_BUFFER_SIZE)))
			return (success_gnl(tmp, storage, buf, line));
		if (!(tmp = ft_strjoin(*storage, buf)))
			return (free_all(*storage, buf, *line));
		ft_safe_free_char(storage);
		*storage = tmp;
	}
}

int			ft_get_next_line(int fd, char **line)
{
	static char	*storage;
	char		*buf;
	char		*tmp;

	buf = NULL;
	if (!line || fd < 0 || GNL_BUFFER_SIZE <= 0)
		return (free_all(storage, buf, NULL));
	*line = NULL;
	if (storage && (tmp = ft_find_new_line(storage, ft_strlen(storage))))
		return (success_gnl(tmp, &storage, buf, line));
	if (!(buf = malloc(GNL_BUFFER_SIZE + 1)))
		return (free_all(storage, buf, *line));
	return (loop_gnl(fd, &storage, buf, line));
}
