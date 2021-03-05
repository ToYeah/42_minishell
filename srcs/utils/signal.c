/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 00:20:59 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/05 16:46:46 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <errno.h>
#include "const.h"
#include "utils.h"

void		handle_signal(int signal)
{
	extern int	g_status;
	int			prev_errno;

	prev_errno = errno;
	ft_putstr_fd(ERASE_SIGNAL_MSG, STDERR_FILENO);
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n"SHELL_PROMPT, STDERR_FILENO);
		g_status = 1;
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
