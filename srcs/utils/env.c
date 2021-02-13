/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 19:17:58 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/14 01:12:35 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

t_env	*create_envs_from_environ(void)
{
	extern char	**environ;
	size_t		i;
	t_env		*envs;
	t_env		*now_env;

	envs = NULL;
	i = 0;
	while (environ[i])
	{
		now_env = create_new_env(environ[i]);
		add_env(&envs, now_env);
		i++;
	}
	return (envs);
}

void	print_envs(t_env *envs)
{
	while (envs)
	{
		ft_putstr_fd(envs->name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putstr_fd(envs->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		envs = envs->next;
	}
}

void	add_env(t_env **envs, t_env *new_env)
{
	if (!new_env || !envs)
		return ;
	if (!*envs)
		*envs = new_env;
	else
	{
		get_last_env(*envs)->next = new_env;
		new_env->next = NULL;
	}
}
