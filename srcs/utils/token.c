/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:05:44 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/27 23:28:40 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "utils.h"

void			del_token(t_token **token_p)
{
	t_token *token;

	if (!token_p || !*token_p)
		return ;
	token = *token_p;
	if (token->data)
		free(token->data);
	if (token->next)
		token->next->prev = token->prev;
	if (token->prev)
		token->prev->next = token->next;
	free(token);
	*token_p = NULL;
}

void			del_token_list(t_token **token_p)
{
	t_token *now;
	t_token *tmp;

	if (!token_p || !*token_p)
		return ;
	now = *token_p;
	while (now)
	{
		tmp = now->next;
		del_token(&now);
		now = tmp;
	}
	*token_p = NULL;
}

t_token_type	judge_token_type(char c)
{
	int			command_count;
	const char	commands[] = {
		'|', '\'', '\"', ' ', ';', '\\', '>', '<', '\0'};

	command_count = 9;
	while (command_count--)
	{
		if (commands[command_count] == c)
			return (commands[command_count]);
	}
	return (CHAR_GENERAL);
}

t_token			*token_init(size_t len, t_token *prev)
{
	t_token *res;

	if (!(res = malloc(sizeof(t_token))))
		error_exit(NULL);
	if (!(res->data = malloc(sizeof(char) * (len + 1))))
		error_exit(NULL);
	res->data[0] = '\0';
	res->type = TOKEN;
	res->next = NULL;
	res->prev = prev;
	return (res);
}
