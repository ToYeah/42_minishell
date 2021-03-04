/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:50:50 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/04 11:40:31 by totaisei         ###   ########.fr       */
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
	extern char *g_pwd;

	if (!(phy_path = join_path(g_pwd, args[1])))
		error_exit(NULL);
	canon_path = path_canonicalisation(phy_path);
	
	printf("%s\n", canon_path);
	chdir(args[1]);
	g_pwd = canon_path;
	free(phy_path);
	return (0);
}