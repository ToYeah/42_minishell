/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:32:52 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/04 14:38:47 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

void	correct_path(char **str)
{
	char	**split;
	char	*res;
	size_t	index;

	if (!str || !*str)
		return ;
	index = 0;
	if (!(split = ft_split(*str, '/')) ||
		!(res = malloc(sizeof(char) * (ft_strlen(*str) + 1))))
		error_exit(NULL);
	ft_safe_free_char(str);
	*str = res;
	*res++ = '/';
	while (split[index])
	{
		if (index != 0)
			*res++ = '/';
		res = ft_strcpy_forward(res, split[index]);
		index++;
	}
	*res = '\0';
	ft_safe_free_split(&split);
}

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

char	*build_full_path(char *path, const char *cmd)
{
	char *cwd;
	char *res;
	char *tmp;

	if (*path == '/')
		return (join_path(path, cmd));
	if (!(cwd = getcwd(NULL, 0)))
		return (NULL);
	if (!(tmp = join_path(cwd, path)))
	{
		free(cwd);
		return (NULL);
	}
	if (!(res = join_path(tmp, cmd)))
	{
		free(cwd);
		free(tmp);
		return (NULL);
	}
	free(cwd);
	free(tmp);
	correct_path(&res);
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
