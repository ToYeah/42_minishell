/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 01:11:20 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 16:47:46 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "utils.h"

t_token	*copy_token(t_token *token)
{
	t_token	*new;
	size_t	data_len;

	data_len = ft_strlen(token->data);
	new = token_init(data_len, NULL);
	ft_strlcpy(new->data, token->data, data_len + 1);
	new->type = token->type;
	return (new);
}

void	add_copied_token(t_token **list, t_token *original_token)
{
	t_token	*now;
	t_token	*copied_token;

	copied_token = copy_token(original_token);
	if (!*list)
		*list = copied_token;
	else
	{
		now = *list;
		while (now->next)
			now = now->next;
		now->next = copied_token;
		copied_token->prev = now->next;
	}
}

t_bool	has_token_type(t_token **token, t_token_type type)
{
	if ((*token)->type == type)
	{
		*token = (*token)->next;
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_redirect_token(t_token *token)
{
	return (token->type == CHAR_GREATER || token->type == CHAR_LESSER ||
		token->type == IO_NUMBER);
}

void	set_redirect_type(t_token *token, t_redirect *redirect)
{
	if (token->type == CHAR_LESSER)
	{
		redirect->type = REDIR_INPUT;
	}
	else if (token->type == CHAR_GREATER)
	{
		redirect->type = REDIR_OUTPUT;
	}
	else if (token->type == D_GREATER)
	{
		redirect->type = REDIR_APPEND_OUTPUT;
	}
	else
	{
		// TODO: error handling
		print_unexpected_token_error(token);
		error_exit();
	}
}

void	parse_io_redirect(t_token **tokens, t_node *command_node)
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

t_node	*parse_command(t_token **tokens)
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

t_node	*parse_pipeline(t_token **tokens)
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

t_node	*parse_complete_command(t_token **tokens)
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
