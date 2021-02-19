/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_ionumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:02:30 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/19 18:44:24 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

t_bool is_nums_token(t_tokeniser *toker)
{
	size_t i;

	if (!toker || !toker->token || !toker->token->data)
	{
		return (FALSE);
	}
	i = toker->tok_i;
	while(i && ft_isdigit(toker->token->data[i - 1]))
	{
		i--;
	}
	if(i == 0)
	{
		return (TRUE);
	}
	return (FALSE);
}