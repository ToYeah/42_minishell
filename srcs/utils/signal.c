/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 00:20:59 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/13 23:57:14 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <errno.h>
#include "const.h"
#include "utils.h"

void		handle_signal(int signal)
{
	extern int		g_status;
	extern t_bool	g_interrupted;
	int				prev_errno;

	prev_errno = errno;
	ft_putstr_fd(BACK_CURSOR, STDERR_FILENO);
	ft_putstr_fd(CLEAR_FROM_CURSOR, STDERR_FILENO);
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n"SHELL_PROMPT, STDERR_FILENO);
		g_status = 1;
		g_interrupted = TRUE;
	}
	errno = prev_errno;
}

void		set_signal_handler(void (*func)(int))
{
	if (signal(SIGINT, func) == SIG_ERR)
	{
		error_exit(NULL);
	}
	if (signal(SIGQUIT, func) == SIG_ERR)
	{
		error_exit(NULL);
	}
}
