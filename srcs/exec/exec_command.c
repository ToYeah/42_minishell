/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/23 18:06:18 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include "builtin.h"
#include "utils.h"

static void	exec_command_node(t_node *node)
{
	extern t_env	*g_envs;
	pid_t			pid;
	int				status;
	char			**args;

	args = convert_args(node->command);
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
		if (execve(args[0], args, generate_environ(g_envs)) < 0)
			error_exit();
	}
	else
	{
		if (pid != waitpid(pid, &status, 0))
			error_exit();
	}
}

static void	exec_command(t_node *nodes)
{
	if (nodes->type == NODE_COMMAND)
	{
		exec_command_node(nodes);
	}
}

static void	exec_pipeline(t_node *nodes)
{
	if (!nodes)
	{
		return ;
	}
	if (nodes->type == NODE_PIPE)
	{
		exec_pipeline(nodes->left);
		exec_pipeline(nodes->right);
	}
	else
	{
		exec_command(nodes);
	}
}

void		exec_nodes(t_node *nodes)
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
		exec_pipeline(nodes);
	}
}
