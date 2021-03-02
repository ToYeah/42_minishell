/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 13:24:58 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/02 11:34:47 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		add_redirect(t_redirect **list, t_redirect *new)
{
	t_redirect	*now;

	if (!*list)
		*list = new;
	else
	{
		now = *list;
		while (now->next)
			now = now->next;
		now->next = new;
		new->next = NULL;
	}
}

t_redirect	*create_redirect(void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redirect)
	{
		error_exit(NULL);
	}
	redirect->fd_io = REDIR_FD_NOT_SPECIFIED;
	redirect->fd_file = REDIR_FD_NOT_SPECIFIED;
	redirect->fd_backup = REDIR_FD_NOT_SPECIFIED;
	redirect->next = NULL;
	redirect->filename = NULL;
	return (redirect);
}

static void	set_redirect_fd(t_redirect *redirect)
{
	if (redirect->fd_io == REDIR_FD_NOT_SPECIFIED)
	{
		if (redirect->type == REDIR_INPUT)
			redirect->fd_io = STDIN_FILENO;
		else
			redirect->fd_io = STDOUT_FILENO;
	}
}

t_bool		set_redirect_type(t_token *token, t_redirect *redirect)
{
	if (token->type == CHAR_LESSER)
	{
		redirect->type = REDIR_INPUT;
	}
	else if (token->type == CHAR_GREATER)
	{
		redirect->type = REDIR_OUTPUT;
	}
	else if (token->type == D_GREATER)
	{
		redirect->type = REDIR_APPEND_OUTPUT;
	}
	else
	{
		return (FALSE);
	}
	set_redirect_fd(redirect);
	return (TRUE);
}

void		del_redirect_list(t_redirect **redirect_p)
{
	t_redirect	*now;
	t_redirect	*tmp;

	if (!redirect_p)
		return ;
	now = *redirect_p;
	while (now)
	{
		tmp = now->next;
		del_token_list(&now->filename);
		free(now);
		now = tmp;
	}
	*redirect_p = NULL;
}
