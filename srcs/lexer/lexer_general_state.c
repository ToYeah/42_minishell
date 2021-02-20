/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_general_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:59:13 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/20 09:53:14 by totaisei         ###   ########.fr       */
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

void	general_sep_process(t_tokeniser *toker, t_token_type type, char *str)
{
	if (is_io_number_token(toker, type))
		toker->token->type = IO_NUMBER;
	tokeniser_add_new_token(toker);
	if (type != CHAR_WHITESPACE)
	{
		toker->token->data[toker->tok_i++] = str[toker->str_i];
		while (str[toker->str_i + 1] == str[toker->str_i])
			toker->token->data[toker->tok_i++] = str[++toker->str_i];
		toker->token->data[toker->tok_i] = '\0';
		if (is_normal_token(toker->token) == FALSE)
		{
			ft_putendl_fd("Commandline contains unknown token.", STDERR_FILENO);
			del_token_list(&(toker->tokens_start));
			return ;
		}
		toker->token->type = type;
		if (type == CHAR_GREATER && ft_strcmp(toker->token->data, ">>") == 0)
			toker->token->type = D_GREATER;
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
