/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 19:17:58 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/09 02:45:37 by nfukada          ###   ########.fr       */
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

char	**generate_environ(t_env *envs)
{
	char	**environ;
	char	*tmp;
	size_t	env_size;
	size_t	i;

	env_size = get_environ_size(envs);
	if (!(environ = (char **)malloc(sizeof(char *) * (env_size + 1))))
		error_exit(NULL);
	i = 0;
	while (i < env_size)
	{
		if (can_generate_environ(envs))
		{
			if (!(environ[i] = ft_strjoin(envs->name, "=")))
				error_exit(NULL);
			tmp = environ[i];
			if (!(environ[i] = ft_strjoin(environ[i], envs->value)))
				error_exit(NULL);
			free(tmp);
			i++;
		}
		envs = envs->next;
	}
	environ[i] = NULL;
	return (environ);
}

t_bool	can_generate_environ(t_env *env)
{
	if (env->value == NULL)
		return (FALSE);
	if (env->is_env == FALSE)
		return (FALSE);
	return (TRUE);
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

void	del_env(t_env **envs, char *name)
{
	t_env	*now;
	t_env	*prev;

	prev = NULL;
	now = *envs;
	while (now)
	{
		if (ft_strncmp(now->name, name, ft_strlen(name) + 1) == 0)
		{
			if (prev)
				prev->next = now->next;
			else
				*envs = now->next;
			free(now);
		}
		prev = now;
		now = now->next;
	}
}
