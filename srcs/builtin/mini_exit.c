/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:59:01 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/04 15:00:58 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Cause the shell to exit with a status of n.  If  n  is  omitted,
** the exit status is that of the last command executed.  A trap on
** EXIT is executed before the shell terminates.
**
** bash-3.2$ exit aaa
** exit
** bash: exit: aaa: numeric argument required
*/

#include <stdlib.h>

int		exec_exit(char **args)
{
	(void)args;
	exit(1);
	return (0);
}
