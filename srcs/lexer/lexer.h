/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:44:34 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/12 18:03:09 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "../../libft/libft.h"

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
};

typedef struct	s_token_list
{
	t_token *tokens;
	size_t	token_count;
}				t_token_list;


#endif