/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_canonicalisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:09:25 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/06 07:56:39 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

char	*cpy_path_elem(char *path_p, char *elem, char *start)
{
	if (ft_strcmp(elem, "..") == 0)
	{
		path_p = ft_strrchr(start, '/');
		if (!path_p)
			path_p = start;
		*path_p = '\0';
	}
	else if (ft_strcmp(elem, ".") != 0)
	{
		path_p = ft_strcpy_forward(path_p, "/");
		path_p = ft_strcpy_forward(path_p, elem);
	}
	return (path_p);
}

t_bool	cpy_canonical_path(char **split, char **res)
{
	char	*start;
	char	*path_p;
	size_t	index;

	start = *res;
	*start = '\0';
	index = 0;
	path_p = start;
	while (split[index])
	{
		path_p = cpy_path_elem(path_p, split[index], start);
		if (path_p == start)
			path_p = ft_strcpy_forward(path_p, "/");
		if (!is_directory(start))
			return (FALSE);
		index++;
	}
	if (path_p == start)
		path_p = ft_strcpy_forward(path_p, "/");
	return (TRUE);
}

char	*path_canonicalisation(char *path)
{
	char			**split;
	char			*res;

	if (!path)
		return (NULL);
	if (!(split = ft_split(path, '/')) ||
		!(res = malloc(sizeof(char *) * (ft_strlen(path) + 1))))
		error_exit(NULL);
	if (!(cpy_canonical_path(split, &res)))
		ft_safe_free_char(&res);
	ft_safe_free_split(&split);
	return (res);
}
