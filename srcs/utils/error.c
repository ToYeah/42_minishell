/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:12:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/01 13:09:46 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "const.h"
#include "libft.h"
#include "token.h"

void	print_error(char *message, char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
}

void	error_exit(char *command)
{
	print_error(strerror(errno), command);
	exit(1);
}

void	print_syntax_error(t_token *token)
{
	extern int	g_status;

	ft_putstr_fd(
		"minishell: syntax error near unexpected token `", STDERR_FILENO);
	if (token)
	{
		ft_putstr_fd(token->data, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("newline", STDERR_FILENO);
	}
	ft_putendl_fd("'", STDERR_FILENO);
	g_status = STATUS_SYNTAX_ERROR;
}

void	print_bad_fd_error(int fd)
{
	char	*fd_str;

	if (fd < 0)
	{
		print_error(strerror(errno), "file descriptor out of range");
	}
	else
	{
		if (!(fd_str = ft_itoa(fd)))
			error_exit(NULL);
		print_error(strerror(errno), fd_str);
		free(fd_str);
	}
}
