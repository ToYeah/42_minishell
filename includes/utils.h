/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:13:16 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 00:33:08 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include "token.h"

typedef struct			s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}						t_env;

typedef struct s_token	t_token;

void					error_exit(void);
void					print_unexpected_token_error(t_token *token);

t_env					*create_envs_from_environ(void);
void					print_envs(t_env *envs);
char					**generate_environ(t_env *envs);
void					add_env(t_env **envs, t_env *new_env);
void					del_env(t_env **envs, char *name);

t_env					*get_last_env(t_env *envs);
size_t					get_env_size(t_env *envs);
t_env					*create_new_env(char *env_str);
const char				*search_env(t_env *envs, char *name);

#endif
