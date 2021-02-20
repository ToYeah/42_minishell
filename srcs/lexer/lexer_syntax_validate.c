/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax_validate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 08:07:01 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/20 09:53:25 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

t_bool is_normal_token(t_token *token)
{
	int			pattern_count;
	const char	*patterns[] = {
		"|", ">", ">>", "<", ";"
	};

	if (!token)
		return (FALSE);
	if(token->type == TOKEN)
		return (TRUE);
	pattern_count = 0;
	while(pattern_count < 5)
	{
		if(ft_strcmp(token->data, (char *)patterns[pattern_count]) == 0)
			return (TRUE);
		pattern_count++;
	}
	return (FALSE);
}

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
