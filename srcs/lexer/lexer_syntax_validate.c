/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax_validate.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 08:07:01 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/20 09:33:49 by totaisei         ###   ########.fr       */
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
