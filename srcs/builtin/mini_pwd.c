/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 12:28:21 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/04 12:31:46 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

int		exec_pwd(char **args)
{
	extern char *g_pwd;
	(void)args;
	ft_putendl_fd(g_pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
