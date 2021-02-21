/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 18:06:00 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "exec.h"
#include "utils.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"

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

void	loop_shell(t_env *envs)
{
	int		status;
	char	*line;
	t_token	*tokens;
	t_token	*start_token;
	t_node	*nodes;

	(void)envs;
	status = 1;
	while (status)
	{
		ft_putstr_fd(SHELL_PROMPT, STDOUT_FILENO);
		if (ft_get_next_line(STDIN_FILENO, &line) < 0)
			error_exit();
		tokens = tokenise(line, 0);
		start_token = tokens;
		if (parse_complete_command(&nodes, &tokens) == FALSE)
			print_unexpected_token_error(tokens);
		// exec_command(args, envs);
		free(line);
		del_token_list(&start_token);
		del_node_list(nodes);
	}
}

int		main(int argc, char *argv[])
{
	t_env	*envs;

	(void)argc;
	(void)argv;
	envs = create_envs_from_environ();
	loop_shell(envs);
}
