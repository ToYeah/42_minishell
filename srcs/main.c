/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/23 18:09:03 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "utils.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"

t_env	*g_envs;

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

void	loop_shell(void)
{
	int		status;
	char	*line;
	int		gnl_result;
	t_token	*tokens;
	t_token	*start_token;
	t_node	*nodes;

	status = 1;
	gnl_result = 1;
	while (status)
	{
		if (gnl_result)
			ft_putstr_fd(SHELL_PROMPT, STDERR_FILENO);
		if ((gnl_result = ft_get_next_line(STDIN_FILENO, &line)) < 0)
			error_exit();
		tokens = tokenise(line, 0);
		start_token = tokens;
		if (parse_complete_command(&nodes, &tokens) == FALSE)
			print_unexpected_token_error(tokens);
		else
			exec_nodes(nodes);
		free(line);
		del_token_list(&start_token);
		del_node_list(nodes);
	}
}

int		main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	g_envs = create_envs_from_environ();
	loop_shell();
}
