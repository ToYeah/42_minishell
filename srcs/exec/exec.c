/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/27 17:14:29 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "builtin.h"
#include "parser.h"
#include "utils.h"
#include "expander.h"

static void		wait_commands(t_command *command)
{
	int	status;

	while (command)
	{
		if (command->pid != NO_PID && waitpid(command->pid, &status, 0) < 0)
		{
			error_exit();
		}
		command = command->next;
	}
}

static void		exec_command(
	t_command *command, t_pipe_state state, int old_pipe[])
{
	extern t_env	*g_envs;
	pid_t			pid;
	char			**args;
	int				new_pipe[2];
	char			*tmp;

	expand_tokens(&command->args);
	args = convert_args(command);
	if (args[0] == NULL)
		return ;
	if (is_builtin(args))
	{
		exec_builtin(args);
		return ;
	}
	tmp = args[0];
	args[0] = build_cmd_path(args[0]);
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
	command->pid = pid;
	free(tmp);
	ft_safe_free_split(&args);
}

static void		exec_pipeline(t_node *nodes)
{
	t_command	*command;
	int			pipe[2];

	while (nodes->type == NODE_PIPE)
		nodes = nodes->left;
	exec_command(nodes->command, PIPE_WRITE_ONLY, pipe);
	command = nodes->command->next;
	while (command->next)
	{
		exec_command(command, PIPE_READ_WRITE, pipe);
		command = command->next;
	}
	exec_command(command, PIPE_READ_ONLY, pipe);
	wait_commands(nodes->command);
}

static void		exec_list(t_node *nodes)
{
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
		exec_command(nodes->command, NO_PIPE, NULL);
		wait_commands(nodes->command);
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
