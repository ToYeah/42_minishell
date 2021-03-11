/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 08:24:01 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/09 21:00:02 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "token.h"

typedef struct	s_expander
{
	size_t			str_i;
	t_token_state	state;
	t_token_type	type;
	char			*str;
}				t_expander;

void			expand_tokens(t_token **tokens);
char			*create_expanded_str(const char *str, t_token_state state,
					t_bool is_env);
char			*expand_env_var(char *input);
char			*dup_env_value(char *name);
#endif
