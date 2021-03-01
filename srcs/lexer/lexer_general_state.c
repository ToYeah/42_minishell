/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:59:13 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/01 10:28:12 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	tokeniser_add_new_token(t_tokeniser *toker)
{
	t_token *tmp_token;

	if (toker->tok_i > 0 || (toker->is_quoted))
	{
		toker->token->data[toker->tok_i] = '\0';
		tmp_token =
			token_init(toker->str_len - toker->str_i, toker->token);
		toker->token->next = tmp_token;
		toker->token = tmp_token;
		toker->tok_i = 0;
		toker->is_quoted = FALSE;
	}
}

t_bool	is_io_number_token(t_tokeniser *toker, t_token_type type)
{
	size_t i;

	if (!toker || !toker->token || !toker->token->data ||
		toker->tok_i == 0 ||
		(type != CHAR_GREATER && type != CHAR_LESSER))
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
	if (is_io_number_token(toker, type))
		toker->token->type = IO_NUMBER;
	tokeniser_add_new_token(toker);
	if (type != CHAR_WHITESPACE && type != CHAR_TAB)
	{
		toker->token->data[toker->tok_i++] = str[toker->str_i];
		if (str[toker->str_i + 1] == str[toker->str_i])
		{
			if (type == CHAR_GREATER)
			{
				toker->token->data[toker->tok_i++] = str[++toker->str_i];
				type = D_GREATER;
			}
			else if (type == CHAR_SEMICOLON)
			{
				toker->token->data[toker->tok_i++] = str[++toker->str_i];
				type = D_SEMICOLON;
			}
		}
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
			toker->is_quoted = TRUE;
			if (toker->esc_flag)
				toker->tok_i -= 1;
		}
		else if (type == CHAR_DQUOTE)
		{
			toker->state = STATE_IN_DQUOTE;
			toker->is_quoted = TRUE;
			if (toker->esc_flag)
				toker->tok_i -= 1;
		}
		else
			toker->state = STATE_GENERAL;
		toker->token->type = TOKEN;
	}
	else
		general_sep_process(toker, type, str);
}
