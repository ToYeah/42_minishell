/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:06:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 18:05:29 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

t_node	*add_parent_node(t_node_type type, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		error_exit();
	node->type = type;
	node->left = left;
	node->right = right;
	return (node);
}

void	set_command_args(t_command *command, t_token **tokens)
{
	while (*tokens && (*tokens)->type == TOKEN)
	{
		add_copied_token(&command->args, *tokens);
		*tokens = (*tokens)->next;
	}
}

t_node	*create_command_node(void)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		error_exit();
	if (!(node->command = (t_command *)malloc(sizeof(t_command))))
		error_exit();
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->command->args = NULL;
	node->command->redirects = NULL;
	return (node);
}

void	del_node_list(t_node *node)
{
	if (!node)
		return ;
	if (node->command)
	{
		del_token_list(&node->command->args);
		del_redirect_list(&node->command->redirects);
		free(node->command);
	}
	del_node_list(node->left);
	del_node_list(node->right);
	free(node);
}
