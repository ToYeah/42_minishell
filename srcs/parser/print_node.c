/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:36:06 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/02 21:02:40 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "lexer.h"
#include "parser.h"

#define DOT_FILE_NAME	"ast.dot"
#define DOT_INDENT		"    "

void	print_edge(t_node *left, t_node *right, int fd)
{
	ft_putstr_fd(DOT_INDENT"NODE_", fd);
	ft_puthex_ul_fd((unsigned long)left, 0, fd);
	ft_putstr_fd(" -> NODE_", fd);
	ft_puthex_ul_fd((unsigned long)right, 0, fd);
	ft_putendl_fd(";", fd);
}

/*
** print node and edge definitions
**     NODE_{node} [label="{node->type}\n{args}\n{redirects}"];
**     NODE_{node} -> NODE_{node->left;}
**     NODE_{node} -> NODE_{node->right;}
*/

void	print_node(t_node *node, int fd)
{
	ft_putstr_fd(DOT_INDENT"NODE_", fd);
	ft_puthex_ul_fd((unsigned long)node, 0, fd);
	print_node_label(node, fd);
	if (node->left)
	{
		print_edge(node, node->left, fd);
	}
	if (node->right)
	{
		print_edge(node, node->right, fd);
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
		error_exit(NULL);
	ft_putstr_fd("digraph AST {\n", fd);
	print_nodes_rec(node, fd);
	ft_putstr_fd("}\n", fd);
	if (close(fd) < 0)
		error_exit(NULL);
}
