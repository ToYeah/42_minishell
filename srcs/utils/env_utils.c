/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:38:53 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/19 11:20:05 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

t_env		*get_last_env(t_env *envs)
{
	t_env	*target;

	if (!envs)
		return (NULL);
	target = envs;
	while (target->next)
		target = target->next;
	return (target);
}

size_t		get_env_size(t_env *envs)
{
	size_t	size;

	size = 0;
	while (envs)
	{
		envs = envs->next;
		size++;
	}
	return (size);
}

t_env		*create_new_env(char *env_str)
{
	t_env	*env;
	char	*sep;

	if (!(env = malloc(sizeof(t_env))))
		error_exit();
	sep = ft_strchr(env_str, '=');
	if (!sep)
		error_exit();
	env->name = ft_substr(env_str, 0, sep - env_str);
	env->value = ft_strdup(sep + 1);
	if (!env->name || !env->value)
		error_exit();
	env->next = NULL;
	return (env);
}

void		free_env(t_env *env)
{
	free(env->name);
	free(env->value);
	env->name = NULL;
	env->value = NULL;
	free(env);
}

const char	*search_env(t_env *envs, char *name)
{
	t_env	*now;

	if (!envs || !name)
		return (NULL);
	now = envs;
	while (now)
	{
		if (ft_strncmp(now->name, name, ft_strlen(name) + 1) == 0)
			return (now->value);
		now = now->next;
	}
	return ("");
}
