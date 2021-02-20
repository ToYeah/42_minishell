/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 01:11:20 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/18 15:29:01 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

t_bool	has_token_type(t_token **token, t_token_type type)
{
	if ((*token)->type == type)
	{
		*token = (*token)->next;
		return (TRUE);
	}
	return (FALSE);
}

// void	parse_io_file(t_token **tokens)
// {
// 	// is_io_file
// 	// is_word
// 		// other
// 			// error: syntax error near unexpected token `newline`
// }

void	parse_io_redirect(t_token **tokens)
{
	(void)tokens;
	// while
		// is_io_file
			// parse_io_file
		// other
			// break
}

t_node	*parse_command(t_token **tokens)
{
	if ((*tokens)->type == TOKEN)
	{
		return (create_command_node(tokens));
	}
	if ((*tokens)->type == CHAR_GREATER || (*tokens)->type == CHAR_LESSER)
	{
	}
	return (NULL);
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

	node = parse_pipeline(tokens);
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
