/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/03 17:41:04 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "utils.h"
#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"

t_env	*g_envs;
int		g_status;
char	*g_pwd;

void	run_commandline(char *line)
{
	t_token	*tokens;
	t_token	*start_token;
	t_node	*nodes;

	tokens = tokenise(line, FALSE);
	start_token = tokens;
	if (parse_complete_command(&nodes, &tokens) == FALSE)
		print_syntax_error(tokens);
	else
		exec_nodes(nodes);
	del_token_list(&start_token);
	del_node_list(nodes);
}

void	loop_shell(void)
{
	char	*line;
	int		gnl_result;

	gnl_result = 1;
	while (TRUE)
	{
		if (gnl_result)
			ft_putstr_fd(SHELL_PROMPT, STDERR_FILENO);
		if ((gnl_result = ft_get_next_line(STDIN_FILENO, &line)) < 0)
			error_exit(NULL);
		run_commandline(line);
		free(line);
	}
}

int		main(int argc, char *argv[])
{
	minishell_init();
	if (argc > 2 && ft_strcmp("-c", argv[1]) == 0)
	{
		run_commandline(argv[2]);
	}
	else
	{
		loop_shell();
	}
	return (g_status);
}
