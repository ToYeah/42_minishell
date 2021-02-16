/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 09:30:46 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/16 19:23:54 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void close_token_list(t_tokeniser *toker)
{
	if(toker->tok_i == 0)
		del_token(&toker->token);
	else
		toker->token->data[toker->tok_i] = '\0';
}

void tokeniser_init(t_tokeniser *toker, char *str)
{
	size_t len;
	t_token *start_token;

	len = ft_strlen(str);
	start_token = token_init(len, NULL);
	toker->token = start_token;
	toker->tokens_start = start_token;
	toker->state = STATE_GENERAL;
	toker->str_i = 0;
	toker->tok_i = 0;
	toker->str_len = len;
	toker->quote_start = NULL;
}

t_token *tokenise_input(char *str)
{
	t_tokeniser toker;
	t_token_type type;

	tokeniser_init(&toker, str);
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
	close_token_list(&toker);
	return toker.tokens_start;
}

t_token *tokenise(char *input)
{
	size_t		input_len;
	t_token		*tokens_start;
	tokens_start = tokenise_input(input);
	return tokens_start;
}
