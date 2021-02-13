/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:38:53 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/14 01:13:06 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

t_env	*get_last_env(t_env *envs)
{
	t_env	*target;

	if (!envs)
		return (NULL);
	target = envs;
	while (target->next)
		target = target->next;
	return (target);
}

t_env	*create_new_env(char *env_str)
{
	t_env	*env;
	char	*sep;

	if (!(env = malloc(sizeof(t_env))))
		error_exit();
	sep = ft_strchr(env_str, '=');
	if (!sep)
	{
		free(env);
		return (NULL);
	}
	*sep = '\0';
	env->name = ft_strdup(env_str);
	env->value = ft_strdup(sep + 1);
	if (!env->name || !env->value)
		error_exit();
	env->next = NULL;
	return (env);
}
