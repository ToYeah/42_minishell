/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 01:11:20 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 17:00:36 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include "utils.h"

static void		parse_io_redirect(t_token **tokens, t_node *command_node)
{
	t_redirect	*redirect;

	redirect = create_redirect();
	if ((*tokens)->type == IO_NUMBER)
	{
		redirect->fd = ft_atoi((*tokens)->data);
		*tokens = (*tokens)->next;
	}
	set_redirect_type(*tokens, redirect);
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN)
	{
		// TODO: error handling
		print_unexpected_token_error(*tokens);
		error_exit();
	}
	add_copied_token(&redirect->filename, *tokens);
	add_redirect(&command_node->command->redirects, redirect);
	*tokens = (*tokens)->next;
}

static t_node	*parse_command(t_token **tokens)
{
	t_node	*command_node;

	if (!*tokens)
	{
		// TODO: error handling
		print_unexpected_token_error(*tokens);
		error_exit();
	}
	command_node = create_command_node();
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN)
		{
			set_command_args(command_node->command, tokens);
		}
		else if (is_redirect_token(*tokens))
		{
			parse_io_redirect(tokens, command_node);
		}
		else
		{
			break ;
		}
	}
	return (command_node);
}

static t_node	*parse_pipeline(t_token **tokens)
{
	t_node	*node;

	node = parse_command(tokens);
	while (*tokens)
	{
		if (has_token_type(tokens, CHAR_PIPE))
		{
			node = add_parent_node(NODE_PIPE, node, parse_command(tokens));
		}
		else
		{
			break ;
		}
	}
	return (node);
}

t_node			*parse_complete_command(t_token **tokens)
{
	t_node	*node;

	node = NULL;
	if (*tokens)
	{
		node = parse_pipeline(tokens);
	}
	while (*tokens)
	{
		if (has_token_type(tokens, CHAR_SEMICOLON))
		{
			node = add_parent_node(
				NODE_SEMICOLON, node, parse_pipeline(tokens));
		}
		else
		{
			break ;
		}
	}
	print_nodes(node);
	return (node);
}
