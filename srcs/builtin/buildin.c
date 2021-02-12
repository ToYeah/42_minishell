/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 23:55:20 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/12 21:04:45 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Cause the shell to exit with a status of n.  If  n  is  omitted,
** the exit status is that of the last command executed.  A trap on
** EXIT is executed before the shell terminates.
**
** bash-3.2$ exit aaa
** exit
** bash: exit: aaa: numeric argument required
*/

void	exec_exit(char **args)
{
	(void)args;
	exit(1);
}

void	exec_cd(char **args)
{
	(void)args;
	ft_putstr_fd("cd called!\n", STDOUT_FILENO);
}

void	exec_builtin(char **args)
{
	if (ft_strncmp(args[0], "exit", ft_strlen("exit") + 1) == 0)
		exec_exit(args);
	if (ft_strncmp(args[0], "cd", ft_strlen("cd") + 1) == 0)
		exec_cd(args);
}

int		is_builtin(char **args)
{
	const char	*commands[] = {
		"exit", "cd", NULL
	};
	int			i;

	i = 0;
	while (commands[i])
	{
		if (ft_strncmp(args[0], commands[i], ft_strlen(commands[i] + 1)) == 0)
			return (1);
		i++;
	}
	return (0);
}
