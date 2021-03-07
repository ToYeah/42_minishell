/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:37:42 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/07 20:35:25 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	print_env(t_env *env)
{
	if (env->value == NULL)
		return ;
	if (env->is_env == FALSE)
		return ;
	ft_putstr_fd(env->name, STDOUT_FILENO);
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putendl_fd(env->value, STDOUT_FILENO);
}

int			exec_env(void)
{
	extern t_env	*g_envs;
	t_env			*env;

	env = g_envs;
	while (env)
	{
		print_env(env);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
