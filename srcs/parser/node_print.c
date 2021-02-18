/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:36:06 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/18 15:51:40 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "parser.h"

#define HEADER "    "

void	print_command_args(t_token *args)
{
	printf("{");
	while (args)
	{
		printf("%s", args->data);
		args = args->next;
		if (args)
			printf(", ");
	}
	printf("}");
}

void	print_node_type(t_node *node)
{
	if (node->type == NODE_SEMICOLON)
		printf("SEMICOLON");
	else if (node->type == NODE_PIPE)
		printf("PIPE");
	else if (node->type == NODE_COMMAND)
		printf("COMMAND");
	else
		printf("unknown");
}

void	print_node(t_node *node)
{
	printf(HEADER"NODE_%p [label=\"", node);
	print_node_type(node);
	printf("\\n");
	if (node->type == NODE_COMMAND)
		print_command_args(node->command->args);
	printf("\"];\n");
	if (node->left)
		printf(HEADER"NODE_%p -> NODE_%p;\n", node, node->left);
	if (node->right)
		printf(HEADER"NODE_%p -> NODE_%p;\n", node, node->right);
}

void	print_nodes_rec(t_node *node)
{
	if (!node)
		return ;
	print_node(node);
	print_nodes_rec(node->left);
	print_nodes_rec(node->right);
}

void	print_nodes(t_node *node)
{
	printf("digraph AST {\n");
	print_nodes_rec(node);
	printf("}\n");
}
