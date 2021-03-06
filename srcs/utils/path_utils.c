/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:32:52 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/12 08:27:55 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

char	*join_path(const char *prev, const char *next)
{
	char	*tmp;
	char	*res;
	size_t	index;

	if (!prev || !next)
		return (NULL);
	tmp = NULL;
	res = NULL;
	if (!(tmp = ft_strjoin(prev, "/")))
		error_exit(NULL);
	index = ft_strlen(tmp);
	if (index >= 2 && tmp[index - 2] == '/')
		tmp[index - 1] = '\0';
	if (!(res = ft_strjoin(tmp, next)))
		error_exit(NULL);
	free(tmp);
	return (res);
}

t_bool	is_directory(const char *path)
{
	t_stat path_stat;

	if (stat(path, &path_stat) == -1)
		return (FALSE);
	if (S_ISDIR(path_stat.st_mode))
		return (TRUE);
	return (FALSE);
}

char	**allocate_colon_unit_parent(const char *str)
{
	size_t	index;
	size_t	colon_count;
	char	**res;

	index = 0;
	colon_count = 0;
	while (str[index])
	{
		if (str[index] == ':')
			colon_count++;
		index++;
	}
	if (!(res = malloc(sizeof(char *) * (colon_count + 2))))
		error_exit(NULL);
	res[colon_count + 1] = NULL;
	return (res);
}

char	*strdup_colon_unit(char *unit, const char *default_value)
{
	char *res;

	if (!unit)
		return (NULL);
	if (ft_strlen(unit) == 0)
	{
		if (!(res = ft_strdup(default_value)))
			error_exit(NULL);
	}
	else
	{
		if (!(res = ft_strdup(unit)))
			error_exit(NULL);
	}
	return (res);
}

char	**get_colon_units(const char *str, const char *default_value)
{
	char	**res;
	size_t	index;
	char	*copied_str;
	char	*unit_start;
	char	*unit_end;

	index = 0;
	res = allocate_colon_unit_parent(str);
	if (!(copied_str = ft_strdup(str)))
		error_exit(NULL);
	unit_start = copied_str;
	unit_end = ft_strchr(unit_start, ':');
	while (unit_end)
	{
		*unit_end = '\0';
		res[index] = strdup_colon_unit(unit_start, default_value);
		unit_start = unit_end + 1;
		unit_end = ft_strchr(unit_start, ':');
		index++;
	}
	res[index] = strdup_colon_unit(unit_start, default_value);
	ft_safe_free_char(&copied_str);
	return (res);
}
