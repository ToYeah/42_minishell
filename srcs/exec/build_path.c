/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:40:22 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/11 13:40:04 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "exec.h"
#include "utils.h"
#include "libft.h"

t_cmd_type	judge_cmd_type(const char *str)
{
	if (*str == '/')
		return (ABSOLUTE);
	else if (ft_strchr(str, '/') != NULL)
		return (RELATIVE);
	else
		return (COMMAND);
}

char		*search_command_binary(const char *cmd)
{
	char	**split_path;
	int		index;
	char	*res;
	char	*path;

	index = 0;
	res = NULL;
	path = NULL;
	if (!(split_path = get_colon_units(get_env_data("PATH"), ".")))
		error_exit(NULL);
	if (split_path[0] == NULL)
		is_command_exist(cmd, &res);
	while (split_path[index])
	{
		ft_safe_free_char(&path);
		path = join_path(split_path[index], cmd);
		if (is_command_exist(path, &res) && !is_directory(path) &&
			is_executable(path))
			break ;
		index++;
	}
	ft_safe_free_char(&path);
	ft_safe_free_split(&split_path);
	return (res);
}

static void	check_cmd_path(const char *cmd, const char *path)
{
	if (path == NULL)
	{
		print_error("command not found", (char *)cmd);
		exit(STATUS_CMD_NOT_FOUND);
	}
}

char		*build_cmd_path(const char *cmd)
{
	t_cmd_type	type;
	char		*res;

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
			error_exit(NULL);
	}
	check_cmd_path(cmd, res);
	return (res);
}
