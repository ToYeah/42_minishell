/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_canonicalisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:09:25 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/11 04:28:17 by totaisei         ###   ########.fr       */
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

void	add_slash_path_front(char *path, char **res)
{
	char *added_res;

	if (!path || !res || !*res)
		return ;
	if (ft_strncmp(path, "//", 2) == 0 && path[2] != '/' &&
		ft_strncmp(*res, "//", 2) != 0)
	{
		if (!(added_res = ft_strjoin("/", *res)))
			error_exit(NULL);
		ft_safe_free_char(res);
		*res = added_res;
	}
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
	add_slash_path_front(path, &res);
	return (res);
}
