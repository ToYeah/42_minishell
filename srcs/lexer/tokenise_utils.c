/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:20:15 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/18 17:51:10 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	general_state_sep(t_tokeniser *toker, t_token_type type, char *str)
{
	char token_char;

	token_char = str[toker->str_i];
	tokeniser_add_front(toker);
	if (type != CHAR_WHITESPACE)
	{
		toker->token->data[toker->tok_i++] = str[toker->str_i];
		while(str[toker->str_i + 1] == token_char)
			toker->token->data[toker->tok_i++] = str[++toker->str_i];
		toker->token->type = type;
		tokeniser_add_front(toker);
	}
}

void	general_state(t_tokeniser *toker, t_token_type type, char *str)
{
	if (type == '\'' || type == '\"' || type == '\\' || type == CHAR_GENERAL)
	{
		if (type == CHAR_ESCAPE && str[toker->str_i + 1] != '\0')
		{
			if(toker->esc_flag)
				toker->token->data[toker->tok_i++] = str[++toker->str_i];
			else
			{
				toker->token->data[toker->tok_i++] = str[toker->str_i++];
				toker->token->data[toker->tok_i++] = str[toker->str_i];
			}
		}
		else
			toker->token->data[toker->tok_i++] = str[toker->str_i];
		if (type == '\'')
		{
			toker->state = STATE_IN_QUOTE;
			toker->quote_start = &toker->token->data[toker->tok_i - 1];
		}
		else if (type == '\"')
		{
			toker->state = STATE_IN_DQUOTE;
			toker->quote_start = &toker->token->data[toker->tok_i - 1];
		}
		else
		{
			toker->state = STATE_GENERAL;
			toker->quote_start = NULL;
		}
		toker->token->type = TOKEN;
	}
	else
		general_state_sep(toker, type, str);
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
		if(toker->esc_flag)
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

void			tokeniser_add_front(t_tokeniser *toker)
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
