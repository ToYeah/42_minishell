/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:44:34 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/16 19:19:29 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../libft/libft.h"

typedef enum	e_tokentype{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_AMPERSAND = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_SEMICOLON = ';',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPESEQUENCE = '\\',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_NULL = 0,
	TOKEN	= -1,
}				t_token_type;

typedef enum	e_token_state{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
}				t_token_state;

typedef struct s_token t_token;

struct	s_token
{
	char *data;
	t_token_type type;
	t_token *next;
	t_token *prev;
};

typedef struct s_tokeniser{
	size_t str_i;
	size_t tok_i;
	size_t str_len;
	t_token_state state;
	t_token *token;
	char *quote_start;
	t_token *tokens_start;
}				t_tokeniser;

char			*envarg_expansion(char *str);
t_token_type	judge_token_type(char c);

void	del_token(t_token **token_p);
void	del_token_list(t_token *token);
t_token_type	judge_token_type(char c);
t_token *token_init(size_t len, t_token *prev);
void token_add_front(t_tokeniser *toker);

t_token *tokenise(char *input);

void general_state_sep(t_tokeniser *toker, t_token_type type, char *str);
void general_state(t_tokeniser *toker, t_token_type type, char *str);
void quote_state(t_tokeniser *toker, t_token_type type, char *str);
void d_quote_state(t_tokeniser *toker, t_token_type type, char *str);
t_bool	is_escape_char(char c, t_token_state state);

#endif