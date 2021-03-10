/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:34:48 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/09 21:42:24 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

int	exec_unset(char **args)
{
	extern t_env	*g_envs;
	size_t			i;
	int				ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (args[i])
	{
		if (is_identifier(args[i]) == TRUE)
		{
			del_env(&g_envs, args[i]);
		}
		else
		{
			print_identifier_error("unset", args[i]);
			ret = EXIT_FAILURE;
		}
		i++;
	}
	return (ret);
}
