/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/12 20:14:07 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "builtin.h"
#include "utils.h"

void	exec_command(char **args, char **envp)
{
	pid_t	pid;
	int		status;

	if (args[0] == NULL)
		return ;
	if (is_builtin(args))
	{
		exec_builtin(args);
		return ;
	}
	if ((pid = fork()) < 0)
		error_exit();
	if (pid == 0)
	{
		if (execve(args[0], args, envp) < 0)
			error_exit();
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
}
