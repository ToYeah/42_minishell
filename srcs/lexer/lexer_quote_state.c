/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:59:05 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/22 17:21:12 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	quote_state(t_tokeniser *toker, t_token_type type, char *str)
{
	(void)type;
	toker->token->data[toker->tok_i++] = str[toker->str_i];
	if (str[toker->str_i] == CHAR_QOUTE)
	{
		toker->state = STATE_GENERAL;
		if (toker->esc_flag == TRUE)
			toker->tok_i -= 1;
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
			if (toker->esc_flag == TRUE)
				toker->tok_i -= 1;
		}
	}
}
