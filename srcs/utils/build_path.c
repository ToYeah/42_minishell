/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:40:22 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/25 15:34:44 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

t_cmd_type judge_cmd_type(const char *str)
{
	if (*str == '/')
		return (ABSOLUTE);
	else if (ft_strchr(str, '/') != NULL)
		return (RELATIVE);
	else
		return (COMMAND);
}

t_bool is_executable_command(char *path)
{
	t_stat buf;

	if (lstat(path, &buf) == -1)
		return (FALSE);
	if (S_ISLNK(buf.st_mode))
	{
		if ((buf.st_mode & S_IXUSR) != S_IXUSR ||
			stat(path, &buf) == -1 ||
			S_ISDIR(buf.st_mode) ||
			(buf.st_mode & S_IXUSR) != S_IXUSR)
		{
			return (FALSE);
		}
	}
	else
	{
		if ((buf.st_mode & S_IXUSR) != S_IXUSR)
			return (FALSE);
	}
	return (TRUE);
}

t_bool is_command_exist(char *path, char **res)
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
		error_exit();
	return (TRUE);
}

char *search_command_binary(const char *cmd)
{
	char	**split_path;
	int		index;
	char	*res;
	char	*path;

	index = 0;
	res = NULL;
	path = build_full_path("", cmd);
	if (!(split_path = ft_split(search_env("PATH"), ':')))
		error_exit();
	if (split_path[0] == NULL)
		is_command_exist(path, &res);
	while (split_path[index])
	{
		ft_safe_free_char(&path);
		path = build_full_path(split_path[index], cmd);
		if (is_command_exist(path, &res) && is_executable_command(path))
				break;
		index++;
	}
	ft_safe_free_char(&path);
	ft_safe_free_split(&split_path);
	return (res);
}

char *build_path(const char *cmd)
{
	t_cmd_type type;
	char *res;
	if (!cmd)
		return (NULL);
	type = judge_cmd_type(cmd);
	if (type == COMMAND)
	{
		res = search_command_binary(cmd);
	}
	else
	{
		if (!(res = ft_strdup(cmd)))
			error_exit();
	}
	return (res);
}

