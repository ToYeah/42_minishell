/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 20:27:33 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/09 21:41:59 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "const.h"
#include "utils.h"

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

void	print_token_error(t_token_state state)
{
	extern int	g_status;

	if (state == STATE_IN_DQUOTE)
		print_error("unexpected EOF while looking for matching `\"'", NULL);
	if (state == STATE_IN_QUOTE)
		print_error("unexpected EOF while looking for matching `''", NULL);
	g_status = STATUS_TOKEN_ERROR;
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

void	print_numeric_argument_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

void	print_identifier_error(char *command, char *name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}
