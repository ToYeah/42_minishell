/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/26 00:15:16 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "builtin.h"
#include "parser.h"
#include "utils.h"

pid_t		exec_command(t_command *command, t_pipe_state state, int old_pipe[])
{
	extern t_env	*g_envs;
	pid_t			pid;
	char			**args;
	int				new_pipe[2];

	args = convert_args(command);
	if (args[0] == NULL)
		return (NO_PID);
	if (is_builtin(args))
	{
		exec_builtin(args);
		return (NO_PID);
	}
	create_pipe(state, new_pipe);
	if ((pid = fork()) < 0)
		error_exit();
	if (pid == 0)
	{
		dup_pipe(state, old_pipe, new_pipe);
		if (execve(args[0], args, generate_environ(g_envs)) < 0)
			error_exit();
	}
	cleanup_pipe(state, old_pipe, new_pipe);
	return (pid);
}

static void		exec_pipeline(t_node *nodes)
{
	t_command	*command;
	pid_t		pid;
	int			pipe[2];
	int			status;

	while (nodes->type == NODE_PIPE)
		nodes = nodes->left;
	exec_command(nodes->command, PIPE_WRITE_ONLY, pipe);
	command = nodes->command->next;
	while (command->next)
	{
		exec_command(command, PIPE_READ_WRITE, pipe);
		command = command->next;
	}
	pid = exec_command(command, PIPE_READ_ONLY, pipe);
	if (waitpid(pid, &status, 0) < 0)
	{
		error_exit();
	}
}

static void		exec_list(t_node *nodes)
{
	pid_t	pid;
	int		status;

	if (!nodes)
	{
		return ;
	}
	if (nodes->type == NODE_PIPE)
	{
		exec_pipeline(nodes);
	}
	else
	{
		pid = exec_command(nodes->command, NO_PIPE, NULL);
		if (pid >= 0 && waitpid(pid, &status, 0) < 0)
		{
			error_exit();
		}
	}
}

void			exec_nodes(t_node *nodes)
{
	if (!nodes)
	{
		return ;
	}
	if (nodes->type == NODE_SEMICOLON)
	{
		exec_nodes(nodes->left);
		exec_nodes(nodes->right);
	}
	else
	{
		exec_list(nodes);
	}
}
