/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:07:01 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/03 00:04:51 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"
# include "lexer.h"

# define REDIR_FD_NOT_SPECIFIED		-1
# define REDIR_FD_OUT_OF_RANGE		-2

# define NO_PID						-1
# define PIPE_IN					1
# define PIPE_OUT					0

typedef struct s_node	t_node;

typedef enum			e_redirect_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUTPUT
}						t_redirect_type;

typedef struct			s_redirect
{
	int					fd_io;
	int					fd_file;
	int					fd_backup;
	t_redirect_type		type;
	t_token				*filename;
	struct s_redirect	*next;
}						t_redirect;

typedef struct			s_command
{
	t_token				*args;
	t_redirect			*redirects;
	pid_t				pid;
	struct s_command	*next;
}						t_command;

typedef enum			e_pipe_state
{
	NO_PIPE,
	PIPE_READ_ONLY,
	PIPE_WRITE_ONLY,
	PIPE_READ_WRITE
}						t_pipe_state;

typedef enum			e_cmd_type
{
	ABSOLUTE,
	RELATIVE,
	COMMAND
}						t_cmd_type;

void					exec_nodes(t_node *nodes);
int						exec_command(t_command *command, t_pipe_state *state,
							int old_pipe[]);

void					create_pipe(t_pipe_state state, int new_pipe[]);
void					dup_pipe(t_pipe_state state, int old_pipe[],
							int new_pipe[]);
void					cleanup_pipe(t_pipe_state state, int old_pipe[],
							int new_pipe[]);

t_bool					setup_redirects(t_command *command);
t_bool					dup_redirects(t_command *command, t_bool is_parent);
void					cleanup_redirects(t_command *command);

t_bool					convert_tokens(t_command *command, char ***args);

char					*build_full_path(char *path, const char *cmd);
char					*build_cmd_path(const char *cmd);
#endif
