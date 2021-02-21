/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_node_label.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 13:42:30 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 23:02:42 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "parser.h"

void	print_command_args(t_token *args, int fd)
{
	while (args)
	{
		ft_putstr_fd(args->data, fd);
		args = args->next;
		if (args)
			ft_putstr_fd(", ", fd);
	}
	ft_putstr_fd("\\n", fd);
}

void	print_redirect(t_redirect *redirect, int fd)
{
	if (redirect->fd != REDIR_FD_NOT_SPECIFIED)
		ft_putnbr_fd(redirect->fd, fd);
	if (redirect->type == REDIR_INPUT)
		ft_putstr_fd("<", fd);
	else if (redirect->type == REDIR_OUTPUT)
		ft_putstr_fd(">", fd);
	else if (redirect->type == REDIR_APPEND_OUTPUT)
		ft_putstr_fd(">>", fd);
	else
		ft_putstr_fd("?", fd);
	ft_putstr_fd(redirect->filename->data, fd);
}

void	print_redirects(t_redirect *redirects, int fd)
{
	while (redirects)
	{
		print_redirect(redirects, fd);
		redirects = redirects->next;
		if (redirects)
			ft_putstr_fd(", ", fd);
	}
}

void	print_node_type(t_node *node, int fd)
{
	if (node->type == NODE_SEMICOLON)
		ft_putstr_fd("SEMICOLON", fd);
	else if (node->type == NODE_PIPE)
		ft_putstr_fd("PIPE", fd);
	else if (node->type == NODE_COMMAND)
		ft_putstr_fd("COMMAND", fd);
	else
		ft_putstr_fd("unknown", fd);
}

void	print_node_label(t_node *node, int fd)
{
	ft_putstr_fd(" [label=\"", fd);
	print_node_type(node, fd);
	ft_putstr_fd("\\n", fd);
	if (node->type == NODE_COMMAND)
	{
		print_command_args(node->command->args, fd);
		print_redirects(node->command->redirects, fd);
	}
	ft_putstr_fd("\"];\n", fd);
}
