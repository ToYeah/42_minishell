/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:59:52 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/22 17:38:59 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "parser.h"
#include "builtin.h"
#include "utils.h"

static void	exec_command_node(t_node *node)
{
	pid_t	pid;
	int		status;
	char	**args;

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
		// TODO: set envs
		if (execve(args[0], args, generate_environ(NULL)) < 0)
			error_exit();
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
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
