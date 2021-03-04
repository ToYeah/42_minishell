/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 14:59:01 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/04 17:02:01 by nfukada          ###   ########.fr       */
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

#include <errno.h>
#include "libft.h"
#include "utils.h"

int		exec_exit(char **args)
{
	extern int		g_status;
	extern t_bool	g_interactive;
	int				i;
	int				status;

	i = 1;
	if (g_interactive == TRUE)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (args[i] && ft_strcmp(args[i], "--") == 0)
		i++;
	if (args[i] == NULL)
		exit(g_status);
	errno = 0;
	status = ft_atoi(args[i]);
	if (errno || is_digit_str(args[i]) == FALSE)
	{
		print_numeric_argument_error(args[i]);
		exit(255);
	}
	if (args[i + 1])
	{
		print_error("too many arguments", "exit");
		return (EXIT_FAILURE);
	}
	exit(status);
	return (EXIT_FAILURE);
}