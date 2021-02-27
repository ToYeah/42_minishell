/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/27 23:29:19 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include "utils.h"

static void		wait_commands(t_command *command)
{
	int	status;

	while (command)
	{
		if (command->pid != NO_PID && waitpid(command->pid, &status, 0) < 0)
		{
			error_exit(NULL);
		}
		command = command->next;
	}
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
