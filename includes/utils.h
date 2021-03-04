/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:13:16 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/02 02:12:13 by nfukada          ###   ########.fr       */
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
	struct s_env	*next;
}				t_env;

typedef struct stat	t_stat;

void			error_exit(char *command);
void			print_error(char *message, char *command);
void			print_syntax_error(t_token *token);
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
#endif
