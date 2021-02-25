/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/25 23:39:25 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include "builtin.h"
#include "utils.h"

#define NO_PID		-1
#define PIPE_IN		0
#define PIPE_OUT	1

static void		create_pipe(t_pipe_state state, int new_pipe[])
{
	if (state == PIPE_WRITE_ONLY || state == PIPE_READ_WRITE)
	{
		if (pipe(new_pipe) < 0)
			error_exit();
	}
}

static void		dup_pipe(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (state == PIPE_READ_ONLY || state == PIPE_READ_WRITE)
	{
		if (close(old_pipe[PIPE_OUT]) < 0 ||
			dup2(old_pipe[PIPE_IN], STDIN_FILENO) < 0 ||
			close(old_pipe[PIPE_IN] < 0))
		{
			error_exit();
		}
	}
	if (state == PIPE_WRITE_ONLY || state == PIPE_READ_WRITE)
	{
		if (close(new_pipe[PIPE_IN]) < 0 ||
			dup2(new_pipe[PIPE_OUT], STDOUT_FILENO) < 0 ||
			close(new_pipe[PIPE_OUT]) < 0)
		{
			error_exit();
		}
	}
}

static void		cleanup_pipe(
	t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (state == PIPE_READ_ONLY || state == PIPE_READ_WRITE)
	{
		if (close(old_pipe[PIPE_IN]) < 0 ||
			close(old_pipe[PIPE_OUT]))
		{
			error_exit();
		}
	}
	if (state == PIPE_WRITE_ONLY || state == PIPE_READ_WRITE)
	{
		old_pipe[PIPE_IN] = new_pipe[PIPE_IN];
		old_pipe[PIPE_OUT] = new_pipe[PIPE_OUT];
	}
}

static pid_t	exec_command(
	t_command *command, t_pipe_state state, int old_pipe[])
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
