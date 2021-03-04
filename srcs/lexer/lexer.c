/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 20:01:44 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/03 14:41:13 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

void	close_token_list(t_tokeniser *toker)
{
	if (!toker->tokens_start)
		return ;
	if (toker->state != STATE_GENERAL)
	{
		print_token_error(toker->state);
		del_token_list(&(toker->tokens_start));
		return ;
	}
	if (toker->tok_i == 0 && toker->is_quoted == FALSE)
	{
		if (toker->tokens_start == toker->token)
			del_token_list(&toker->tokens_start);
		else
			del_token(&toker->token);
	}
	else
		toker->token->data[toker->tok_i] = '\0';
}

void	tokeniser_init(t_tokeniser *toker, char *str, t_bool esc_flag)
{
	size_t	len;
	t_token	*start_token;

	len = ft_strlen(str);
	start_token = token_init(len, NULL);
	toker->token = start_token;
	toker->tokens_start = start_token;
	toker->state = STATE_GENERAL;
	toker->str_i = 0;
	toker->tok_i = 0;
	toker->str_len = len;
	toker->esc_flag = esc_flag;
	toker->is_quoted = FALSE;
}

t_token	*tokenise(char *str, t_bool esc_flag)
{
	t_tokeniser		toker;
	t_token_type	type;

	if (!str)
		return (NULL);
	tokeniser_init(&toker, str, esc_flag);
	while (str[toker.str_i] != '\0' && toker.tokens_start)
	{
		type = judge_token_type(str[toker.str_i]);
		if (toker.state == STATE_GENERAL)
			general_state(&toker, type, str);
		else if (toker.state == STATE_IN_QUOTE)
			quote_state(&toker, type, str);
		else if (toker.state == STATE_IN_DQUOTE)
			d_quote_state(&toker, type, str);
		toker.str_i++;
	}
	close_token_list(&toker);
	return (toker.tokens_start);
}
