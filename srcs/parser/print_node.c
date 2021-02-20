/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:36:06 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 00:08:56 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lexer.h"
#include "parser.h"

#define DOT_FILE_NAME	"ast.dot"
#define DOT_INDENT		"    "

void	print_command_args(t_token *args, int fd)
{
	while (args)
	{
		ft_putstr_fd(args->data, fd);
		args = args->next;
		if (args)
			ft_putstr_fd(", ", fd);
	}
}

void	print_node_type(t_node *node, int fd)
{
	if (node->type == NODE_SEMICOLON)
		ft_putstr_fd("SEMICOLON", fd);
	else if (node->type == NODE_PIPE)
		ft_putstr_fd("PIPE", fd);
	else if (node->type == NODE_COMMAND)
		ft_putstr_fd("COMMAND", fd);
	else
		ft_putstr_fd("unknown", fd);
}

/*
** print node and edge definitions
**     NODE_{node} [label="{node->type}\n{args}"];
**     NODE_{node} -> NODE_{node->left;}
**     NODE_{node} -> NODE_{node->right;}
*/

void	print_node(t_node *node, int fd)
{
	ft_putstr_fd(DOT_INDENT"NODE_", fd);
	ft_puthex_ul_fd((unsigned long)node, 0, fd);
	ft_putstr_fd(" [label=\"", fd);
	print_node_type(node, fd);
	ft_putstr_fd("\\n", fd);
	if (node->type == NODE_COMMAND)
		print_command_args(node->command->args, fd);
	ft_putstr_fd("\"];\n", fd);
	if (node->left)
	{
		ft_putstr_fd(DOT_INDENT"NODE_", fd);
		ft_puthex_ul_fd((unsigned long)node, 0, fd);
		ft_putstr_fd(" -> NODE_", fd);
		ft_puthex_ul_fd((unsigned long)node->left, 0, fd);
		ft_putendl_fd(";", fd);
	}
	if (node->right)
	{
		ft_putstr_fd(DOT_INDENT"NODE_", fd);
		ft_puthex_ul_fd((unsigned long)node, 0, fd);
		ft_putstr_fd(" -> NODE_", fd);
		ft_puthex_ul_fd((unsigned long)node->right, 0, fd);
		ft_putendl_fd(";", fd);
	}
}

void	print_nodes_rec(t_node *node, int fd)
{
	if (!node)
		return ;
	print_node(node, fd);
	print_nodes_rec(node->left, fd);
	print_nodes_rec(node->right, fd);
}

void	print_nodes(t_node *node)
{
	int	fd;

	fd = open(DOT_FILE_NAME, O_TRUNC | O_CREAT | O_WRONLY, 0755);
	if (fd < 0)
		error_exit();
	ft_putstr_fd("digraph AST {\n", fd);
	print_nodes_rec(node, fd);
	ft_putstr_fd("}\n", fd);
	close(fd);
}
