/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 17:19:26 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/22 13:06:30 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "lexer.h"

#define NOW 0
#define LAST 1
#define EXPANDED 2
#define RES_LIST 3

void	expand_tokens(t_token **tokens)
{
	t_token	*vars[4];
	char	*expanded_str;

	if (!tokens || !*tokens)
		return ;
	vars[LAST] = NULL;
	vars[RES_LIST] = NULL;
	vars[NOW] = *tokens;
	while (vars[NOW] != NULL)
	{
		expanded_str = expand_env_var(vars[NOW]->data);
		vars[EXPANDED] = tokenise(expanded_str, TRUE);
		free(expanded_str);
		if (vars[RES_LIST] == NULL)
			vars[RES_LIST] = vars[EXPANDED];
		token_join(vars[LAST], vars[EXPANDED]);
		vars[LAST] = find_last_token(vars[RES_LIST]);
		vars[NOW] = vars[NOW]->next;
	}
	del_token_list(tokens);
	*tokens = vars[RES_LIST];
}
