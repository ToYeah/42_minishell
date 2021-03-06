/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 10:58:17 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/09 21:34:29 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

int		exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (exec_exit(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (exec_cd(args));
	if (ft_strcmp(args[0], "echo") == 0)
		return (exec_echo(args));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (exec_pwd());
	if (ft_strcmp(args[0], "env") == 0)
		return (exec_env());
	if (ft_strcmp(args[0], "export") == 0)
		return (exec_export(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (exec_unset(args));
	return (EXIT_FAILURE);
}

int		is_builtin(char **args)
{
	const char	*commands[] = {
		"exit", "cd", "echo", "pwd", "env", "export", "unset", NULL
	};
	int			i;

	i = 0;
	if (args[0] == NULL)
		return (0);
	while (commands[i])
	{
		if (ft_strcmp(args[0], (char *)commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
