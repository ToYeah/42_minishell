/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/16 13:36:27 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include "utils.h"

static void		exec_pipeline(t_node *nodes)
{
	extern int		g_status;
	t_command		*command;
	int				pipe[2];
	t_pipe_state	pipe_state;

	pipe_state = PIPE_WRITE_ONLY;
	while (nodes->type == NODE_PIPE)
		nodes = nodes->left;
	command = nodes->command;
	while (command)
	{
		g_status = exec_command(command, &pipe_state, pipe);
		command = command->next;
	}
	wait_commands(nodes->command);
}

static void		exec_list(t_node *nodes)
{
	extern int		g_status;
	t_pipe_state	pipe_state;

	pipe_state = NO_PIPE;
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
		g_status = exec_command(nodes->command, &pipe_state, NULL);
		wait_commands(nodes->command);
	}
}

void			exec_nodes(t_node *nodes)
{
	extern t_bool g_exited;

	if (!nodes || g_exited == TRUE)
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
