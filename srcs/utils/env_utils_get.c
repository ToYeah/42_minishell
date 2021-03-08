/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:35:53 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/08 13:44:05 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

t_bool		can_generate_environ(t_env *env)
{
	if (env->value == NULL)
		return (FALSE);
	if (env->is_env == FALSE)
		return (FALSE);
	return (TRUE);
}

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

size_t		get_environ_size(t_env *envs)
{
	size_t	size;

	size = 0;
	while (envs)
	{
		if (can_generate_environ(envs))
			size++;
		envs = envs->next;
	}
	return (size);
}

t_env		*get_env(const char *name)
{
	t_env			*now;
	extern t_env	*g_envs;

	if (!g_envs || !name)
		return (NULL);
	now = g_envs;
	while (now)
	{
		if (ft_strcmp(now->name, (char *)name) == 0)
			return (now);
		now = now->next;
	}
	return (NULL);
}

const char	*get_env_data(char *name)
{
	t_env			*now;
	extern t_env	*g_envs;

	if (!g_envs || !name)
		return (NULL);
	now = g_envs;
	while (now)
	{
		if (ft_strcmp(now->name, name) == 0)
		{
			if (!now->value)
				return ("");
			else
				return (now->value);
		}
		now = now->next;
	}
	return ("");
}
