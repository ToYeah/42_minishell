/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:08:55 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/06 22:01:38 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include "exec.h"
#include "expander.h"

static char	**convert_args(t_command *command)
{
	char	**args;
	t_token	*now_token;
	size_t	len;
	size_t	i;

	len = 0;
	now_token = command->args;
	while (now_token)
	{
		now_token = now_token->next;
		len++;
	}
	if (!(args = (char **)malloc(sizeof(char *) * (len + 1))))
		error_exit(NULL);
	now_token = command->args;
	i = 0;
	while (now_token)
	{
		if (!(args[i] = ft_strdup(now_token->data)))
			error_exit(NULL);
		now_token = now_token->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

t_bool		convert_tokens(t_command *command, char ***args)
{
	expand_tokens(&command->args);
	*args = convert_args(command);
	if (*args[0] == NULL)
	{
		return (FALSE);
	}
	return (TRUE);
}

static void	handle_command_status(int status, t_bool catch_sigint)
{
	extern int	g_status;
	int			signal;

	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		g_status = signal + 128;
	}
	if (catch_sigint)
		ft_putendl_fd("", STDERR_FILENO);
}

void		wait_commands(t_command *command)
{
	extern int	g_status;
	int			status;
	t_bool		has_child;
	t_bool		catch_sigint;

	has_child = FALSE;
	catch_sigint = FALSE;
	while (command)
	{
		if (command->pid != NO_PID)
		{
			if (waitpid(command->pid, &status, 0) < 0)
				error_exit(NULL);
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
				catch_sigint = TRUE;
			has_child = TRUE;
		}
		command = command->next;
	}
	if (has_child == FALSE)
		return ;
	handle_command_status(status, catch_sigint);
}
