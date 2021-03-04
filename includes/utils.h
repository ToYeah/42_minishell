/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:13:16 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/04 11:42:25 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <sys/stat.h>
# include "token.h"

typedef struct	s_env
{
	char			*name;
	char			*value;
	t_bool			is_env;
	struct s_env	*next;
}				t_env;

typedef struct stat	t_stat;

void			error_exit(char *command);
void			print_error(char *message, char *command);
void			print_syntax_error(t_token *token);
void			print_token_error(t_token_state state);
void			print_bad_fd_error(int fd);
void			print_numeric_argument_error(char *arg);

t_env			*create_envs_from_environ(void);
void			print_envs(t_env *envs);
char			**generate_environ(t_env *envs);
void			add_env(t_env **envs, t_env *new_env);
void			del_env(t_env **envs, char *name);

t_env			*get_last_env(t_env *envs);
size_t			get_env_size(t_env *envs);
t_env			*create_new_env(char *env_str);
const char		*get_env_data(char *name);
t_env			*get_env(const char *name);
void			minishell_init(void);
void			shlvl_init(void);
char			*join_path(const char *prev, const char *next);
char			*build_full_path(char *path, const char *cmd);
char			*path_canonicalisation(char *path);
t_bool			is_digit_str(char *str);

#endif
