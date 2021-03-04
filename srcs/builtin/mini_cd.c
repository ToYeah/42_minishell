/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:50:50 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/04 16:15:16 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <stdio.h>

#define CWD_CMD_ERR_MSG "error retrieving current directory"
#define CWD_ERR_MSG "getcwd: cannot access parent directories"

char	*get_cwd_path(char *caller)
{
	char *cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
	{
		ft_putstr_fd(caller, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(CWD_CMD_ERR_MSG, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(CWD_ERR_MSG, STDERR_FILENO);
		ft_putstr_fd(": " , STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (cwd);
}

char	*get_new_pwd(char *path, t_bool is_canon_path,t_bool is_abs_path)
{
	char *new_pwd;

	new_pwd = NULL;
	if (is_abs_path)
	{
		if (is_canon_path == FALSE)
			new_pwd = get_cwd_path("cd");
		if (is_canon_path || new_pwd == NULL)
		{
			if (!(new_pwd = ft_strdup(path)))
				error_exit(NULL);
		}
	}
	else
	{
		if (!(new_pwd = get_cwd_path("cd")))
		{
			if (!(new_pwd = ft_strdup(path)))
				error_exit(NULL);
		}
	}
	return (new_pwd);
}

int		change_dir_process(char *cd_path, char *arg, t_bool is_canon_path)
{
	int		res;
	int		err;
	extern char *g_pwd;

	res = chdir(cd_path);
	if (res == 0)
	{
		ft_safe_free_char(&g_pwd);
		g_pwd = get_new_pwd(cd_path, is_canon_path, TRUE);
		return (res);
	}
	err = errno;
	res = chdir(arg);
	if (res == 0)
	{
		ft_safe_free_char(&g_pwd);
		g_pwd = get_new_pwd(cd_path, is_canon_path, FALSE);
		return (res);
	}
	errno = err;
	return (res);
}

t_bool	set_cd_path(char **cd_path, char *arg)
{
	char		*canon_path;
	char		*physical_path;
	t_bool		res;
	extern char	*g_pwd;

	if (!(physical_path = join_path(g_pwd, arg)))
		error_exit(NULL);
	canon_path = path_canonicalisation(physical_path);
	if (canon_path && is_directory(canon_path))
	{
		if (!(*cd_path = ft_strdup(canon_path)))
			error_exit(NULL);
		res = TRUE;
	}
	else
	{
		if (!(*cd_path = ft_strdup(physical_path)))
			error_exit(NULL);
		res = FALSE;
	}
	ft_safe_free_char(&canon_path);
	ft_safe_free_char(&physical_path);
	return res;
}

int		exec_cd(char **args)
{
	char *cd_path;
	t_bool is_canon_path;

	extern char *g_pwd;
	is_canon_path = set_cd_path(&cd_path, args[1]);
	change_dir_process(cd_path, args[1], is_canon_path);
	return (0);
}