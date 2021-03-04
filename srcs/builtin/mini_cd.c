/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:50:50 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/04 12:45:23 by totaisei         ###   ########.fr       */
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

char *get_cwd_path(char *caller)
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


int		exec_cd(char **args)
{
	char *canon_path;
	char *phy_path;
	char *cd_path;
	t_bool is_canon_path;
	int err;

	extern char *g_pwd;

	if (!(phy_path = join_path(g_pwd, args[1])))
		error_exit(NULL);
	ft_safe_free_char(&g_pwd);
	canon_path = path_canonicalisation(phy_path);
	if (canon_path && is_directory(canon_path))
	{
		cd_path = canon_path;
		is_canon_path = TRUE;
	}
	else
	{
		cd_path = phy_path;
		is_canon_path = FALSE;
	}

	if (chdir(cd_path) == 0)
	{
		if (is_canon_path == FALSE)
		{
			g_pwd = get_cwd_path("cd");
		}
		if (is_canon_path || g_pwd == NULL)
		{
			if (!(g_pwd = ft_strdup(cd_path)))
				error_exit(NULL);
		}
	}
	else
	{
		err = errno;
		if (chdir(args[1]) == 0)
		{
			if (!(g_pwd = get_cwd_path("cd")))
			{
				if(!(g_pwd = ft_strdup(phy_path)))
					error_exit(NULL);
			}
		}
		errno = err;
	}
	return (0);
}