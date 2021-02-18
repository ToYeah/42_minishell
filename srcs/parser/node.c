/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:06:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/18 15:43:08 by nfukada          ###   ########.fr       */
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
	t_token	*now_token;

	command->args = NULL;
	while (*tokens && (*tokens)->type == TOKEN)
	{
		if (!command->args)
			command->args = *tokens;
		*tokens = (*tokens)->next;
	}
	if (command->args)
	{
		now_token = command->args;
		while (now_token)
		{
			if (!now_token->next || now_token->next->type != TOKEN)
			{
				now_token->next = NULL;
				break ;
			}
			now_token = now_token->next;
		}
	}
}

t_node	*create_command_node(t_token **tokens)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		error_exit();
	if (!(node->command = (t_command *)malloc(sizeof(t_command))))
		error_exit();
	node->type = NODE_COMMAND;
	set_command_args(node->command, tokens);
	node->left = NULL;
	node->right = NULL;
	return (node);
}
