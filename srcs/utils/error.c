/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:12:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/27 12:39:54 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "const.h"
#include "libft.h"
#include "token.h"

void	error_exit(void)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
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
