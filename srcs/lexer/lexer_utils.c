/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 20:01:50 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/19 11:39:06 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	general_sep_process(t_tokeniser *toker, t_token_type type, char *str)
{
	char token_char;

	token_char = str[toker->str_i];
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

void	quote_state(t_tokeniser *toker, t_token_type type, char *str)
{
	(void)type;
	toker->token->data[toker->tok_i++] = str[toker->str_i];
	if (str[toker->str_i] == CHAR_QOUTE)
	{
		toker->state = STATE_GENERAL;
	}
}

void	d_quote_state(t_tokeniser *toker, t_token_type type, char *str)
{
	if (type == CHAR_ESCAPE && str[toker->str_i + 1] != '\0' &&
		ft_strchr("\"\\$", str[toker->str_i + 1]) != NULL)
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
		if (str[toker->str_i] == CHAR_DQUOTE)
		{
			toker->state = STATE_GENERAL;
		}
	}
}
