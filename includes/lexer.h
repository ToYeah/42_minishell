/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:44:34 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/18 17:46:44 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "token.h"

typedef struct s_tokeniser{
	size_t str_i;
	size_t tok_i;
	size_t str_len;
	t_token_state state;
	t_token *token;
	char *quote_start;
	t_token *tokens_start;
	t_bool esc_flag;
}				t_tokeniser;


t_token *tokenise(char *input, t_bool esc_flag);

void general_state_sep(t_tokeniser *toker, t_token_type type, char *str);
void general_state(t_tokeniser *toker, t_token_type type, char *str);
void quote_state(t_tokeniser *toker, t_token_type type, char *str);
void d_quote_state(t_tokeniser *toker, t_token_type type, char *str);
char **cmdline_split(char *str, int depth, int *depth_res);
void			tokeniser_add_front(t_tokeniser *toker);
#endif