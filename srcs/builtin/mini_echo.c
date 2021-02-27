/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 11:11:48 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/27 12:38:56 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

t_bool	is_option_str(char *str)
{
	size_t len;

	if (!str)
		return (FALSE);
	len = ft_strlen(str);
	if (len < 2 || str[0] != '-' || str[1] != 'n')
		return (FALSE);
	str++;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (TRUE);
	return (FALSE);
}

int		exec_echo(char **args)
{
	size_t index;
	t_bool option_flag;

	index = 1;
	option_flag = FALSE;
	while (args[index])
	{
		if (is_option_str(args[index]))
			option_flag = TRUE;
		else
			break ;
		index++;
	}
	while (args[index])
	{
		ft_putstr_fd(args[index], STDOUT_FILENO);
		if (args[index + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		index++;
	}
	if (option_flag == FALSE)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
