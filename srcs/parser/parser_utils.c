/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:58:32 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 18:31:46 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static t_token	*copy_token(t_token *token)
{
	t_token	*new;
	size_t	data_len;

	data_len = ft_strlen(token->data);
	new = token_init(data_len, NULL);
	ft_strlcpy(new->data, token->data, data_len + 1);
	new->type = token->type;
	return (new);
}

void			add_copied_token(t_token **list, t_token *original_token)
{
	t_token	*now;
	t_token	*copied_token;

	copied_token = copy_token(original_token);
	if (!*list)
		*list = copied_token;
	else
	{
		now = *list;
		while (now->next)
			now = now->next;
		now->next = copied_token;
		copied_token->prev = now->next;
	}
}

t_bool			has_token_type(t_token **token, t_token_type type)
{
	if ((*token)->type == type)
	{
		*token = (*token)->next;
		return (TRUE);
	}
	return (FALSE);
}

t_bool			is_redirect_token(t_token *token)
{
	return (token->type == CHAR_GREATER || token->type == CHAR_LESSER ||
		token->type == D_GREATER || token->type == IO_NUMBER);
}
