/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:07:08 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/12 18:06:20 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

t_bool	is_same_dir(const char *dir_1, const char *dir_2)
{
	t_stat stat1;
	t_stat stat2;

	if (!dir_1 || !dir_2)
		return (FALSE);
	if (stat(dir_1, &stat1) < 0 ||
		stat(dir_2, &stat2) < 0)
	{
		return (FALSE);
	}
	if (stat1.st_ino == stat2.st_ino)
		return (TRUE);
	return (FALSE);
}

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
		old_pwd_env->is_env = TRUE;
		add_env(&g_envs, old_pwd_env);
	}
	ft_safe_free_char(&(old_pwd_env->value));
}

void	pwd_value_init(t_env *pwd_env)
{
	char			*cwd;
	extern char		*g_pwd;

	if (!(cwd = getcwd(NULL, 0)))
		error_exit(NULL);
	if (!pwd_env->value || !is_same_dir(pwd_env->value, cwd))
	{
		if (!(pwd_env->value = ft_strdup(cwd)))
			error_exit(NULL);
	}
	if (!(g_pwd = ft_strdup(pwd_env->value)))
		error_exit(NULL);
	free(cwd);
}

void	pwd_init(void)
{
	t_env			*pwd_env;
	extern t_env	*g_envs;
	extern char		*g_pwd;

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
		pwd_env->is_env = TRUE;
		add_env(&g_envs, pwd_env);
	}
	pwd_value_init(pwd_env);
}

void	minishell_init(void)
{
	extern t_env *g_envs;

	g_envs = create_envs_from_environ();
	pwd_init();
	shlvl_init();
	old_pwd_init();
}
