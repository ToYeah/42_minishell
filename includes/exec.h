/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:07:01 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/19 22:16:21 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"
# include "lexer.h"

typedef enum	e_redirect_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUTPUT
}				t_redirect_type;

typedef struct	s_redirect
{
	t_redirect_type		type;
	t_token				*filename;
	struct s_redirect	*next;
}				t_redirect;

typedef struct	s_command
{
	t_token				*args;
	t_redirect			*redirects;
}				t_command;

void			exec_command(char **args, t_env *envs);

#endif
