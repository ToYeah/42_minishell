/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:07:01 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/23 12:06:51 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"
# include "lexer.h"

# define REDIR_FD_NOT_SPECIFIED		-1
# define REDIR_FD_OUT_OF_RANGE		-2

typedef struct s_node	t_node;

typedef enum			e_redirect_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUTPUT
}						t_redirect_type;

typedef struct			s_redirect
{
	int					fd;
	t_redirect_type		type;
	t_token				*filename;
	struct s_redirect	*next;
}						t_redirect;

typedef struct			s_command
{
	t_token				*args;
	t_redirect			*redirects;
}						t_command;

void					exec_nodes(t_node *nodes);

char					**convert_args(t_command *command);

char					*build_path(char *cmd);
#endif
