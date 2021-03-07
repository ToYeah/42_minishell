/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:28:21 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/07 11:11:14 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"
#include "utils.h"

void	bind_pwd_value(void)
{
	extern char *g_pwd;

	update_env_value("OLDPWD", get_env_data("PWD"), FALSE);
	update_env_value("PWD", g_pwd, FALSE);
}

int		exec_pwd(void)
{
	extern char *g_pwd;

	ft_putendl_fd(g_pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
