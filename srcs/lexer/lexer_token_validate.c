/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_validate.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 07:16:47 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/21 07:17:12 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

t_bool	is_io_number_token(t_tokeniser *toker, t_token_type type)
{
	size_t i;

	if (!toker || !toker->token || !toker->token->data ||
		toker->tok_i == 0 ||
		(type != CHAR_GREATER && type != CHAR_LESSER))
	{
		return (FALSE);
	}
	i = toker->tok_i;
	while (i != 0 && ft_isdigit(toker->token->data[i - 1]))
	{
		i--;
	}
	if (i == 0)
	{
		return (TRUE);
	}
	return (FALSE);
}
