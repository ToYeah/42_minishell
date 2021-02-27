/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 00:08:56 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/27 01:50:42 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	can_write(t_pipe_state state)
{
	if (state == PIPE_WRITE_ONLY || state == PIPE_READ_WRITE)
	{
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	can_read(t_pipe_state state)
{
	if (state == PIPE_READ_ONLY || state == PIPE_READ_WRITE)
	{
		return (TRUE);
	}
	return (FALSE);
}

void			create_pipe(t_pipe_state state, int new_pipe[])
{
	if (can_write(state) == TRUE)
	{
		if (pipe(new_pipe) < 0)
		{
			error_exit();
		}
	}
}

void			dup_pipe(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (can_read(state) == TRUE)
	{
		close(old_pipe[PIPE_IN]);
		if (dup2(old_pipe[PIPE_OUT], STDIN_FILENO) < 0)
		{
			error_exit();
		}
		close(old_pipe[PIPE_OUT]);
	}
	if (can_write(state) == TRUE)
	{
		close(new_pipe[PIPE_OUT]);
		if (dup2(new_pipe[PIPE_IN], STDOUT_FILENO) < 0)
		{
			error_exit();
		}
		close(new_pipe[PIPE_IN]);
	}
}

void			cleanup_pipe(t_pipe_state state, int old_pipe[], int new_pipe[])
{
	if (can_read(state) == TRUE)
	{
		close(old_pipe[PIPE_OUT]);
		close(old_pipe[PIPE_IN]);
	}
	if (can_write(state) == TRUE)
	{
		old_pipe[PIPE_OUT] = new_pipe[PIPE_OUT];
		old_pipe[PIPE_IN] = new_pipe[PIPE_IN];
	}
}
