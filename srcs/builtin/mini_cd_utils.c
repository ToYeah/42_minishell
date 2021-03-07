/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 14:49:01 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/07 11:02:51 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

char	*get_cwd_path(char *caller)
{
	char *cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
	{
		ft_putstr_fd(caller, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("error retrieving current directory", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("getcwd: cannot access parent directories", STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (cwd);
}

char	*get_new_pwd(char *path, t_bool is_canon_path, t_bool is_abs_path)
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

int		change_dir_process(char *cd_path, const char *arg, t_bool is_canon_path)
{
	int			res;
	int			err;
	extern char	*g_pwd;

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
	res = EXIT_FAILURE;
	return (res);
}

char	*set_cd_path(const char *arg, t_bool *is_canon_path)
{
	char		*canon_path;
	char		*physical_path;
	extern char *g_pwd;

	if (*arg == '/')
		physical_path = ft_strdup(arg);
	else
		physical_path = join_path(g_pwd, arg);
	if (!physical_path)
		error_exit(NULL);
	canon_path = path_canonicalisation(physical_path);
	if (canon_path)
	{
		ft_safe_free_char(&physical_path);
		*is_canon_path = TRUE;
		return (canon_path);
	}
	else
	{
		ft_safe_free_char(&canon_path);
		*is_canon_path = FALSE;
		return (physical_path);
	}
}

t_bool	try_change_dir(const char *destination)
{
	char		*path;
	t_bool		is_canon_path;
	int			res;

	path = set_cd_path(destination, &is_canon_path);
	res = change_dir_process(path, destination, is_canon_path);
	ft_safe_free_char(&path);
	if (res == 0)
		return (TRUE);
	return (FALSE);
}
