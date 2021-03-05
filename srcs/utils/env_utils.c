/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:38:53 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/05 10:27:40 by totaisei         ###   ########.fr       */
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

void		update_env_value(
	const char *env_name, const char *new_value, t_bool is_env_var)
{
	t_env		*env;

	if (!env_name)
		return ;
	if (!(env = get_env(env_name)))
	{
		env = create_new_env((char *)env_name);
		env->is_env = is_env_var;
	}
	ft_safe_free_char(&env->value);
	if (new_value)
	{
		if (!(env->value = ft_strdup(new_value)))
			error_exit(NULL);
	}
	else
	{
		env->value = NULL;
	}
}
