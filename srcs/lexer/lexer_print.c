/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 22:08:02 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/11 14:23:02 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

static void	print_token_type(t_token_type type)
{
	if (type == CHAR_GENERAL)
		ft_putstr_fd("GENERAL   ", STDOUT_FILENO);
	else if (type == CHAR_WHITESPACE)
		ft_putstr_fd("WHITESPACE", STDOUT_FILENO);
	else if (type == CHAR_TAB)
		ft_putstr_fd("TAB       ", STDOUT_FILENO);
	else if (type == CHAR_NULL)
		ft_putstr_fd("NULL      ", STDOUT_FILENO);
	else if (type == D_SEMICOLON)
		ft_putstr_fd(";;        ", STDOUT_FILENO);
	else if (type == D_GREATER)
		ft_putstr_fd(">>        ", STDOUT_FILENO);
	else if (type == IO_NUMBER)
		ft_putstr_fd("IO_NUMBER ", STDOUT_FILENO);
	else if (type == TOKEN)
		ft_putstr_fd("TOKEN     ", STDOUT_FILENO);
	else
	{
		ft_putchar_fd(type, STDOUT_FILENO);
		ft_putstr_fd("         ", STDOUT_FILENO);
	}
}

/*
** format: [index]type: TYPE       [data]
*/

void		print_token_list(t_token *tokens, t_bool esc_flag)
{
	int	index;

	index = 0;
	while (tokens)
	{
		ft_putstr_fd("[", STDOUT_FILENO);
		ft_putnbr_fd(index, STDOUT_FILENO);
		ft_putstr_fd("]type: ", STDOUT_FILENO);
		print_token_type(tokens->type);
		ft_putchar_fd('[', STDOUT_FILENO);
		ft_putstr_fd(tokens->data, STDOUT_FILENO);
		ft_putendl_fd("]", STDOUT_FILENO);
		tokens = tokens->next;
		index++;
	}
	if (esc_flag == TRUE)
		ft_putendl_fd("--------------------------------", STDOUT_FILENO);
	else
		ft_putendl_fd("================================", STDOUT_FILENO);
}
