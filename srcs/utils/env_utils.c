/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:38:53 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/05 10:09:32 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

t_env		*create_new_env(char *env_str)
{
	t_env	*env;
	char	*sep;

	if (!(env = malloc(sizeof(t_env))))
		error_exit(NULL);
	sep = ft_strchr(env_str, '=');
	if (!sep)
	{
		if (!(env->name = ft_strdup(env_str)))
			error_exit(NULL);
		env->value = NULL;
	}
	else
	{
		if (!(env->name = ft_substr(env_str, 0, sep - env_str)) ||
			!(env->value = ft_strdup(sep + 1)))
			error_exit(NULL);
	}
	env->is_env = TRUE;
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
