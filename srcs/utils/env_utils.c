/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 23:38:53 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/09 18:22:18 by nfukada          ###   ########.fr       */
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

static void	set_env_value(t_env *env, const char *new_value, t_bool append_flag)
{
	char	*old_value;

	old_value = env->value;
	if (append_flag == TRUE)
	{
		if (old_value || new_value)
		{
			if (!(env->value = ft_strjoin(old_value, new_value)))
				error_exit(NULL);
		}
		else
			env->value = NULL;
	}
	else
	{
		if (new_value)
		{
			if (!(env->value = ft_strdup(new_value)))
				error_exit(NULL);
		}
		else
			env->value = NULL;
	}
	ft_safe_free_char(&old_value);
}

void		update_env_value(const char *env_name, const char *new_value,
	t_bool is_env_var, t_bool append_flag)
{
	extern t_env	*g_envs;
	t_env			*env;

	if (!env_name)
		return ;
	if (!(env = get_env(env_name)))
	{
		env = create_new_env((char *)env_name);
		env->is_env = is_env_var;
		add_env(&g_envs, env);
	}
	else
	{
		if (env->is_env == FALSE)
			env->is_env = is_env_var;
		if (!new_value)
			return ;
	}
	set_env_value(env, new_value, append_flag);
}

t_env		*copy_envs(t_env *envs)
{
	t_env	*res;
	t_env	*now_env;
	t_env	*copy_env;

	now_env = envs;
	res = NULL;
	while (now_env)
	{
		if ((copy_env = (t_env *)malloc(sizeof(t_env))) == NULL)
			error_exit(NULL);
		copy_env->name = now_env->name;
		copy_env->value = now_env->value;
		copy_env->is_env = now_env->is_env;
		copy_env->next = NULL;
		add_env(&res, copy_env);
		now_env = now_env->next;
	}
	return (res);
}
