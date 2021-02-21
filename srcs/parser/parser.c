/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 01:11:20 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/22 01:00:40 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"
#include "utils.h"

static t_bool	parse_io_redirect(t_token **tokens, t_node *command_node)
{
	t_redirect	*redirect;

	redirect = create_redirect();
	if ((*tokens)->type == IO_NUMBER)
	{
		if (ft_atoi_limit((*tokens)->data, &redirect->fd) == FALSE)
			redirect->fd = REDIR_FD_OUT_OF_RANGE;
		*tokens = (*tokens)->next;
	}
	if (set_redirect_type(*tokens, redirect) == FALSE)
	{
		del_redirect_list(&redirect);
		return (FALSE);
	}
	*tokens = (*tokens)->next;
	if (!*tokens || (*tokens)->type != TOKEN)
	{
		del_redirect_list(&redirect);
		return (FALSE);
	}
	add_copied_token(&redirect->filename, *tokens);
	add_redirect(&command_node->command->redirects, redirect);
	*tokens = (*tokens)->next;
	return (TRUE);
}

static t_bool	parse_command(t_node **node, t_token **tokens)
{
	if (!*tokens)
		return (FALSE);
	*node = create_command_node();
	while (*tokens)
	{
		if ((*tokens)->type == TOKEN)
			set_command_args((*node)->command, tokens);
		else if (is_redirect_token(*tokens))
		{
			if (parse_io_redirect(tokens, *node) == FALSE)
			{
				del_node_list(*node);
				*node = NULL;
				return (FALSE);
			}
		}
		else
			break ;
	}
	if (!(*node)->command->args && !(*node)->command->redirects)
		return (FALSE);
	return (TRUE);
}

static t_bool	parse_pipeline(t_node **node, t_token **tokens)
{
	t_node	*child;

	if (parse_command(node, tokens) == FALSE)
	{
		return (FALSE);
	}
	while (*tokens)
	{
		if (has_token_type(tokens, CHAR_PIPE))
		{
			if (parse_command(&child, tokens) == FALSE)
			{
				return (FALSE);
			}
			*node = add_parent_node(NODE_PIPE, *node, child);
		}
		else
		{
			break ;
		}
	}
	return (TRUE);
}

t_bool			parse_complete_command(t_node **nodes, t_token **tokens)
{
	t_node	*child;

	*nodes = NULL;
	if (*tokens)
	{
		if (parse_pipeline(nodes, tokens) == FALSE)
			return (FALSE);
	}
	while (*tokens)
	{
		if (has_token_type(tokens, CHAR_SEMICOLON) && *tokens)
		{
			if (parse_pipeline(&child, tokens) == FALSE)
				return (FALSE);
			*nodes = add_parent_node(NODE_SEMICOLON, *nodes, child);
		}
		else
			break ;
	}
	if (*tokens)
		return (FALSE);
	print_nodes(*nodes);
	return (TRUE);
}
