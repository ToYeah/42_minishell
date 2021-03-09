/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 00:11:32 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/09 18:16:12 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

static t_bool	is_identifier(char *name)
{
	size_t	i;

	i = 0;
	if (name[i] != '_' && !ft_isalpha(name[i]))
		return (FALSE);
	i++;
	while (name[i])
	{
		if (name[i] != '_' && !ft_isalnum(name[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void		separate_arg(char *arg, char **sep, char **value,
	t_bool *append_flag)
{
	*sep = ft_strchr(arg, '=');
	if (*sep)
	{
		**sep = '\0';
		if (*(*sep - 1) == '+')
		{
			*(*sep - 1) = '\0';
			*append_flag = TRUE;
		}
		*value = *sep + 1;
	}
	else
		*value = NULL;
}

static void		restore_arg(char *sep, t_bool append_flag)
{
	if (sep)
	{
		*sep = '=';
		if (append_flag == TRUE)
			*(sep - 1) = '+';
	}
}

static int		set_envs(char **args)
{
	size_t	i;
	char	*sep;
	char	*value;
	t_bool	append_flag;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	value = NULL;
	while (args[i])
	{
		append_flag = FALSE;
		separate_arg(args[i], &sep, &value, &append_flag);
		if (is_identifier(args[i]))
			update_env_value(args[i], value, TRUE, append_flag);
		else
		{
			restore_arg(sep, append_flag);
			print_identifier_error("export", args[i]);
			ret = EXIT_FAILURE;
		}
		i++;
	}
	return (ret);
}

int				exec_export(char **args)
{
	if (args[1])
	{
		return (set_envs(args));
	}
	else
	{
		return (print_envs());
	}
	return (EXIT_SUCCESS);
}
