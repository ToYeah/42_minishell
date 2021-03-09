/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 02:50:02 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/09 15:49:14 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"

static void	print_env(t_env *env)
{
	char	*escaped_value;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->name, STDOUT_FILENO);
	if (env->value)
	{
		escaped_value = create_expanded_str(env->value, STATE_IN_DQUOTE);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(escaped_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(escaped_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static int	compare_env(t_env *left, t_env *right)
{
	return (ft_strcmp(left->name, right->name));
}

int			print_envs(void)
{
	extern t_env	*g_envs;
	t_env			*envs;
	t_env			*tmp;

	envs = copy_envs(g_envs);
	env_mergesort(&envs, compare_env);
	while (envs)
	{
		print_env(envs);
		tmp = envs->next;
		free(envs);
		envs = tmp;
	}
	return (EXIT_SUCCESS);
}
