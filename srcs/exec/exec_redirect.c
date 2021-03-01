/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 10:43:56 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/01 13:10:07 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "exec.h"

#define FILE_MODE	0644

static int	open_file(t_redirect *redir)
{
	char *filename;

	filename = redir->filename->data;
	if (redir->type == REDIR_INPUT)
		return (open(filename, O_RDONLY));
	if (redir->type == REDIR_OUTPUT)
		return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE));
	return (open(filename, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE));
}

static void	cleanup_redirects(t_command *command)
{
	t_redirect	*redir;

	redir = command->redirects;
	while (redir)
	{
		close(redir->fd_file);
		redir = redir->next;
	}
}

t_bool		setup_redirects(t_command *command)
{
	t_redirect	*redir;

	redir = command->redirects;
	while (redir)
	{
		redir->fd_file = open_file(redir);
		if (redir->fd_file < 0)
		{
			cleanup_redirects(command);
			print_error(strerror(errno), redir->filename->data);
			return (FALSE);
		}
		redir = redir->next;
	}
	return (TRUE);
}

t_bool		dup_redirects(t_command *command)
{
	t_redirect	*redir;
	int			dup_to;

	redir = command->redirects;
	while (redir)
	{
		dup_to = redir->fd_io;
		if (redir->fd_io == REDIR_FD_NOT_SPECIFIED)
		{
			if (redir->type == REDIR_INPUT)
				dup_to = STDIN_FILENO;
			else
				dup_to = STDOUT_FILENO;
		}
		if (dup2(redir->fd_file, dup_to) < 0)
		{
			print_bad_fd_error(dup_to);
			close(redir->fd_file);
			return (FALSE);
		}
		close(redir->fd_file);
		redir = redir->next;
	}
	return (TRUE);
}
