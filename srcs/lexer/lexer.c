/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:00:52 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/15 18:21:33 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"


void close_token_list(t_token *last_token, size_t token_index)
{
	if(token_index == 0)
		del_token(&last_token);
	else
		last_token->data[token_index] = '\0';
}

void tokeniser_init(t_tokeniser *toker,t_token *start_token, size_t len)
{
	toker->token = start_token;
	toker->state = STATE_GENERAL;
	toker->str_i = 0;
	toker->tok_i = 0;
	toker->str_len = len;
	toker->quote_start = NULL;
}

void tokenise_input(char *str, t_token *start_token, size_t len)
{
	t_tokeniser toker;
	t_token_type type;

	tokeniser_init(&toker, start_token, len);
	while (str[toker.str_i] != '\0')
	{
		type = judge_token_type(str[toker.str_i]);
		if(toker.state == STATE_GENERAL)
			general_state(&toker, type, str);
		else if(toker.state == STATE_IN_QUOTE)
			quote_state(&toker, type, str);
		else if(toker.state == STATE_IN_DQUOTE)
			d_quote_state(&toker, type, str);
		toker.str_i++;
	}
	close_token_list(toker.token, toker.tok_i);
}

t_token *tokenise(char *input)
{
	size_t		input_len;
	t_token		*start_token;

	input_len = ft_strlen(input);
	start_token = token_init(input_len, NULL);
	if(input_len == 0)
		return start_token;
	tokenise_input(input, start_token, input_len);
	return start_token;
}
