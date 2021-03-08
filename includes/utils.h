/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:13:16 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/08 00:03:56 by nfukada          ###   ########.fr       */
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
void			print_error_filename(char *message,
					char *command, char *file);

t_env			*create_envs_from_environ(void);
char			**generate_environ(t_env *envs);
void			add_env(t_env **envs, t_env *new_env);
void			del_env(t_env **envs, char *name);

t_env			*get_last_env(t_env *envs);
size_t			get_environ_size(t_env *envs);
t_bool			can_generate_environ(t_env *env);
t_env			*create_new_env(char *env_str);
const char		*get_env_data(char *name);
t_env			*get_env(const char *name);
void			minishell_init(void);
void			shlvl_init(void);
char			*join_path(const char *prev, const char *next);
char			*path_canonicalisation(char *path);
t_bool			is_digit_str(char *str);
t_bool			is_directory(const char *path);
void			update_env_value(const char *env_name,
					const char *new_value, t_bool is_env_var);

void			set_signal_handler(void (*func)(int));
void			handle_signal(int signal);

#endif
