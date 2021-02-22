/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:19:26 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/22 12:09:53 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"
#include "utils.h"

void expand_tokens(t_token **tokens)
{
	t_token *now_token;
	t_token *last_token;
	t_token *res_tokens;
	t_token *expanded_token;
	char *expanded_str;

	if (!tokens || !*tokens)
		return ;
	last_token = NULL;
	res_tokens = NULL;
	now_token = *tokens;
	while (now_token != NULL)
	{
		expanded_str = expand_env_var(now_token->data);
		expanded_token = tokenise(expanded_str, TRUE);
		free(expanded_str);
		if (res_tokens == NULL)
			res_tokens = expanded_token;
		token_join(last_token, expanded_token);
		last_token = find_last_token(res_tokens);
		now_token = now_token->next;
	}
	del_token_list(tokens);
	
	*tokens = res_tokens;
}