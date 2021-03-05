/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:50:50 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/05 14:40:58 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <stdio.h>

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

int		change_dir_process(char *cd_path,const char *arg, t_bool is_canon_path)
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
	res = EXIT_FAILURE;
	return (res);
}

char	*set_cd_path(const char *arg, t_bool *flag)
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
	if (canon_path && is_directory(canon_path))
	{
		ft_safe_free_char(&physical_path);
		*flag = TRUE;
		return (canon_path);
	}
	else
	{
		ft_safe_free_char(&canon_path);
		*flag = FALSE;
		return (physical_path);
	}
}

const char	*set_cd_destination(char **args)
{
	t_env	*home_env;
	size_t	index;

	index = 0;
	while (args[index])
		index++;
	if (index >= 3)
	{
		print_error("too many arguments", "cd");
		return (NULL);
	}
	if (index == 1)
	{
		if (!(home_env = get_env("HOME")))
		{
			print_error("HOME not set", "cd");
			return (NULL);
		}
		if (!home_env->value)
			return ("");
		return (home_env->value);
	}
	return (args[1]);
}

t_bool		try_change_dir(const char *destination)
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

t_bool		try_env_dir(const char *dest)
{
	size_t		index;
	char		**split_env;
	char		*joined_dest;
	t_bool		res;

	index = 0;
	res = FALSE;
	joined_dest = NULL;
	if (!(split_env = ft_split(get_env_data("CDPATH"), ':')))
		error_exit(NULL);
	while (split_env[index])
	{
		joined_dest = join_path(split_env[index], dest);
		if (try_change_dir(joined_dest) == 0)
			break ;
		ft_safe_free_char(&joined_dest);
		index++;
	}
	if (split_env[index])
		res = TRUE;
	ft_safe_free_char(&joined_dest);
	ft_safe_free_split(&split_env);
	return (res);
}

int		exec_cd(char **args)
{
	const char	*destination;
	extern char *g_pwd;

	if (!(destination = set_cd_destination(args)))
		return (EXIT_FAILURE);
	if (try_env_dir(destination))
	{
		ft_putendl_fd(g_pwd, STDOUT_FILENO);
		bind_pwd_valie();
		return (EXIT_SUCCESS);
	}
	if (try_change_dir(destination))
	{
		bind_pwd_valie();
		return (EXIT_SUCCESS);
	}
	print_error(strerror(errno), "cd");
	return (EXIT_FAILURE);
}