/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:07:08 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/28 18:29:50 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "utils.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"

void	old_pwd_init(void)
{
	t_env			*old_pwd_env;
	extern t_env	*g_envs;

	old_pwd_env = get_env("OLDPWD");
	if (!old_pwd_env)
	{
		if (!(old_pwd_env = malloc(sizeof(t_env))) ||
			!(old_pwd_env->name = ft_strdup("OLDPWD")))
		{
			error_exit(NULL);
		}
		old_pwd_env->value = NULL;
		old_pwd_env->next = NULL;
		add_env(&g_envs, old_pwd_env);
	}
}

void	pwd_init(void)
{
	t_env			*pwd_env;
	extern t_env	*g_envs;

	pwd_env = get_env("PWD");
	if (!pwd_env)
	{
		if (!(pwd_env = malloc(sizeof(t_env))) ||
			!(pwd_env->name = ft_strdup("PWD")))
		{
			error_exit(NULL);
		}
		pwd_env->value = NULL;
		pwd_env->next = NULL;
		add_env(&g_envs, pwd_env);
	}
	if (!pwd_env->value)
	{
		if (!(pwd_env->value = getcwd(NULL, 0)))
			error_exit(NULL);
	}
}

void	minishell_init(void)
{
	extern t_env *g_envs;

	g_envs = create_envs_from_environ();
	pwd_init();
	shlvl_init();
	old_pwd_init();
}
