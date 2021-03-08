/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path_stat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 21:44:06 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/08 21:57:22 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "utils.h"

t_bool		is_executable(const char *path)
{
	t_stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (FALSE);
	if ((path_stat.st_mode & S_IXUSR) != S_IXUSR)
		return (FALSE);
	if ((path_stat.st_mode & S_IRUSR) != S_IRUSR)
		return (FALSE);
	return (TRUE);
}

t_bool		is_command_exist(const char *path, char **res)
{
	t_stat buf;

	if (!path)
		return (FALSE);
	if (lstat(path, &buf) == -1)
		return (FALSE);
	if (S_ISDIR(buf.st_mode))
		return (FALSE);
	ft_safe_free_char(res);
	if (!(*res = ft_strdup(path)))
		error_exit(NULL);
	return (TRUE);
}
