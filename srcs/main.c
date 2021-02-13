/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/12 22:37:07 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "exec.h"
#include "utils.h"
#include "libft.h"

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

void	loop_shell(char **envp)
{
	int		status;
	char	*line;
	char	**args;

	status = 1;
	while (status)
	{
		ft_putstr_fd(SHELL_PROMPT, STDOUT_FILENO);
		if (ft_get_next_line(STDIN_FILENO, &line) < 0)
			error_exit();
		if ((args = ft_split(line, ' ')) == NULL)
			error_exit();
		free(line);
		exec_command(args, envp);
		free_array(args);
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	loop_shell(envp);
}
