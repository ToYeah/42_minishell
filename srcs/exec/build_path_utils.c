/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:32:52 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/27 23:27:09 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

char	*join_path(const char *prev, const char *next)
{
	char *tmp;
	char *res;

	if (!prev || !next)
		return (NULL);
	tmp = NULL;
	res = NULL;
	if (!(tmp = ft_strjoin(prev, "/")) ||
		!(res = ft_strjoin(tmp, next)))
	{
		error_exit(NULL);
	}
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
	return (res);
}
