/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:07:08 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/28 18:23:43 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "utils.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"

#include <stdio.h>

t_bool	is_digit_str(char *str)
{
	size_t index;

	index = 0;
	while (str[index] == ' ')
		index++;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			break ;
		index++;
	}
	if (str[index] == '\0')
		return (TRUE);
	else
		return (FALSE);
}

void	put_shvl_warning(int num)
{
	char	*str_num;
	char	*tmp;
	char	*msg;

	if (!(str_num = ft_itoa(num)) ||
		!(tmp = ft_strjoin("shell level (", str_num)) ||
		!(msg = ft_strjoin(tmp, ") too high, resetting to 1")))
	{
		error_exit(NULL);
	}
	print_error(msg, "warning");
	free(str_num);
	free(tmp);
	free(msg);
}

char	*calc_shlvl(char *shlvl)
{
	char	*res;
	int		num;

	num = ft_atoi_overflow_zero(shlvl);
	if (!is_digit_str(shlvl))
		num = 0;
	num++;
	if (num == 1000)
		res = ft_strdup("");
	else if (num < 1)
		res = ft_strdup("0");
	else if (0 < num && num < 1000)
		res = ft_itoa(num);
	else
	{
		put_shvl_warning(num);
		res = ft_strdup("1");
	}
	return (res);
}

void	shlvl_init(void)
{
	t_env			*shlvl_env;
	extern t_env	*g_envs;

	shlvl_env = get_env("SHLVL");
	if (!shlvl_env)
	{
		if (!(shlvl_env = malloc(sizeof(t_env))) ||
			!(shlvl_env->name = ft_strdup("SHLVL")) ||
			!(shlvl_env->value = ft_strdup("1")))
		{
			error_exit(NULL);
		}
		shlvl_env->next = NULL;
		add_env(&g_envs, shlvl_env);
		return ;
	}
	else
	{
		if (!(shlvl_env->value = calc_shlvl(shlvl_env->value)))
			error_exit(NULL);
	}
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
