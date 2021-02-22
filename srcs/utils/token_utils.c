/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:09:15 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/22 13:09:16 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token	*find_last_token(t_token *tokens)
{
	t_token *now;

	if (!tokens)
		return (NULL);
	now = tokens;
	while (now->next != NULL)
	{
		now = now->next;
	}
	return (now);
}

size_t	calc_tokens_len(t_token *tokens)
{
	t_token	*now;
	size_t	res;

	res = 0;
	if (!tokens)
		return (res);
	now = tokens;
	while (now != NULL)
	{
		res++;
		now = now->next;
	}
	return (res);
}

void	token_join(t_token *prev_token, t_token *next_token)
{
	if (!prev_token || !next_token ||
		prev_token == next_token)
		return ;
	prev_token->next = next_token;
	next_token->prev = prev_token;
}
