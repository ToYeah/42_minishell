/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:44:34 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/18 18:45:28 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "token.h"
# include "utils.h"

typedef struct	s_tokeniser{
	size_t			str_i;
	size_t			tok_i;
	size_t			str_len;
	t_bool			esc_flag;
	t_token			*token;
	t_token			*tokens_start;
	t_token_state	state;
	char			*quote_start;
}				t_tokeniser;

t_token			*tokenise(char *input, t_bool esc_flag);
void			general_sep_process(t_tokeniser *t, t_token_type y, char *s);
void			general_state(t_tokeniser *t, t_token_type y, char *s);
void			quote_state(t_tokeniser *t, t_token_type y, char *s);
void			d_quote_state(t_tokeniser *t, t_token_type y, char *s);
void			tokeniser_add_front(t_tokeniser *toker);
#endif
