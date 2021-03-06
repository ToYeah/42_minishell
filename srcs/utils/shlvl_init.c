/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 18:27:08 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/12 18:34:45 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

t_bool	is_digit_str(char *str)
{
	size_t	index;
	t_bool	has_digit;

	index = 0;
	has_digit = FALSE;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index])
	{
		if (ft_isdigit(str[index]))
			has_digit = TRUE;
		else
			break ;
		index++;
	}
	while (str[index] == ' ' || str[index] == '\t')
		index++;
	if (str[index] == '\0' && has_digit == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

void	put_shlvl_warning(int num)
{
	char	*str_num;
	char	*tmp;
	char	*msg;

	str_num = NULL;
	tmp = NULL;
	msg = NULL;
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

void	calc_shlvl(char **shlvl)
{
	char	*res;
	int		num;

	num = ft_atoi_overflow_zero(*shlvl);
	if (!is_digit_str(*shlvl))
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
		put_shlvl_warning(num);
		res = ft_strdup("1");
	}
	ft_safe_free_char(shlvl);
	*shlvl = res;
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
		shlvl_env->is_env = TRUE;
		add_env(&g_envs, shlvl_env);
		return ;
	}
	else
	{
		calc_shlvl(&(shlvl_env->value));
		if (!(shlvl_env->value))
			error_exit(NULL);
	}
}
