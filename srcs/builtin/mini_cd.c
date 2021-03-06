/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:50:50 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/06 07:14:25 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"
#include "utils.h"
#include <errno.h>
#include <string.h>

const char	*set_cd_destination(char **args)
{
	t_env	*home_env;
	size_t	index;

	index = 0;
	while (args[index])
		index++;
	if (index == 1)
	{
		if (!(home_env = get_env("HOME")))
		{
			print_error("HOME not set", "cd");
			return (NULL);
		}
		if (!home_env->value)
			return ("");
		return (home_env->value);
	}
	return (args[1]);
}

t_bool		try_env_path(const char *dest)
{
	size_t		index;
	char		**split_env;
	char		*joined_dest;
	t_bool		res;

	index = 0;
	res = FALSE;
	joined_dest = NULL;
	if (!(split_env = ft_split(get_env_data("CDPATH"), ':')))
		error_exit(NULL);
	while (split_env[index])
	{
		joined_dest = join_path(split_env[index], dest);
		if (try_change_dir(joined_dest))
			break ;
		ft_safe_free_char(&joined_dest);
		index++;
	}
	if (split_env[index])
		res = TRUE;
	ft_safe_free_char(&joined_dest);
	ft_safe_free_split(&split_env);
	return (res);
}

t_bool		needs_env_path_search(char **args, const char *dest)
{
	if (args[1] == NULL)
		return (FALSE);
	if (ft_strcmp((char *)dest, ".") == 0 ||
		ft_strcmp((char *)dest, "..") == 0 ||
		ft_strncmp((char *)dest, "./", 2) == 0 ||
		ft_strncmp((char *)dest, "../", 3) == 0)
	{
		return (FALSE);
	}
	return (TRUE);
}

int			exec_cd(char **args)
{
	const char	*dest;
	extern char *g_pwd;

	if (!(dest = set_cd_destination(args)))
		return (EXIT_FAILURE);
	if (needs_env_path_search(args, dest))
	{
		if (try_env_path(dest))
		{
			ft_putendl_fd(g_pwd, STDOUT_FILENO);
			bind_pwd_value();
			return (EXIT_SUCCESS);
		}
	}
	if (try_change_dir(dest))
	{
		bind_pwd_value();
		return (EXIT_SUCCESS);
	}
	print_error_filename(strerror(errno), "cd", (char *)dest);
	return (EXIT_FAILURE);
}
