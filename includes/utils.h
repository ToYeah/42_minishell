/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:13:16 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/14 01:14:40 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

void			error_exit(void);

t_env			*create_envs_from_environ(void);
void			print_envs(t_env *envs);
void			add_env(t_env **envs, t_env *new_env);

t_env			*get_last_env(t_env *envs);
t_env			*create_new_env(char *env_str);

#endif
