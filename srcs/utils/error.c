/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 20:12:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 00:34:12 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "libft.h"
#include "token.h"

void	error_exit(void)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(1);
}

void	print_unexpected_token_error(t_token *token)
{
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
}
