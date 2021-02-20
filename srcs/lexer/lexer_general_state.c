/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:59:13 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/19 19:29:12 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	tokeniser_add_new_token(t_tokeniser *toker)
{
	t_token *tmp_token;

	if (toker->tok_i > 0)
	{
		toker->token->data[toker->tok_i] = '\0';
		tmp_token =
			token_init(toker->str_len - toker->str_i, toker->token);
		toker->token->next = tmp_token;
		toker->token = tmp_token;
		toker->tok_i = 0;
	}
}

t_bool	is_io_number_token(t_tokeniser *toker)
{
	size_t i;

	if (!toker || !toker->token || !toker->token->data ||
		toker->tok_i == 0)
	{
		return (FALSE);
	}
	i = toker->tok_i;
	while (i != 0 && ft_isdigit(toker->token->data[i - 1]))
	{
		i--;
	}
	if (i == 0)
	{
		return (TRUE);
	}
	return (FALSE);
}

void	general_sep_process(t_tokeniser *toker, t_token_type type, char *str)
{
	char token_char;

	token_char = str[toker->str_i];
	if ((token_char == CHAR_GREATER || token_char == CHAR_LESSER) &&
		is_io_number_token(toker))
	{
		toker->token->type = IO_NUMBER;
	}
	tokeniser_add_new_token(toker);
	if (type != CHAR_WHITESPACE)
	{
		toker->token->data[toker->tok_i++] = str[toker->str_i];
		while (str[toker->str_i + 1] == token_char)
			toker->token->data[toker->tok_i++] = str[++toker->str_i];
		toker->token->type = type;
		tokeniser_add_new_token(toker);
	}
}

void	general_esc_process(t_tokeniser *toker, t_token_type type, char *str)
{
	if (type == CHAR_ESCAPE && str[toker->str_i + 1] != '\0')
	{
		if (toker->esc_flag)
			toker->token->data[toker->tok_i++] = str[++toker->str_i];
		else
		{
			toker->token->data[toker->tok_i++] = str[toker->str_i++];
			toker->token->data[toker->tok_i++] = str[toker->str_i];
		}
	}
	else
	{
		toker->token->data[toker->tok_i++] = str[toker->str_i];
	}
}

void	general_state(t_tokeniser *toker, t_token_type type, char *str)
{
	if (type == CHAR_QOUTE || type == CHAR_DQUOTE
	|| type == CHAR_ESCAPE || type == CHAR_GENERAL)
	{
		general_esc_process(toker, type, str);
		if (type == CHAR_QOUTE)
		{
			toker->state = STATE_IN_QUOTE;
		}
		else if (type == CHAR_DQUOTE)
		{
			toker->state = STATE_IN_DQUOTE;
		}
		else
		{
			toker->state = STATE_GENERAL;
		}
		toker->token->type = TOKEN;
	}
	else
		general_sep_process(toker, type, str);
}
