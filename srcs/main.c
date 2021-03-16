/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:50:22 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/16 13:33:10 by nfukada          ###   ########.fr       */
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
t_bool	g_interactive;
t_bool	g_interrupted;
t_bool	g_exited;

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
	del_node_list(&nodes);
}

void	handle_eof(char *line, char *buf_line)
{
	if (line[0] == '\0' && (buf_line == NULL || g_interrupted == TRUE))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(g_status);
	}
	ft_putstr_fd(CLEAR_FROM_CURSOR, STDERR_FILENO);
}

void	process_input(int *gnl_result, char **buf_line)
{
	char	*line;
	char	*tmp;

	if ((*gnl_result = ft_get_next_line(STDIN_FILENO, &line)) < 0)
		error_exit(NULL);
	if (*gnl_result == 0)
		handle_eof(line, *buf_line);
	if (g_interrupted == TRUE)
		ft_safe_free_char(buf_line);
	tmp = *buf_line;
	if ((*buf_line = ft_strjoin(*buf_line, line)) == NULL)
		error_exit(NULL);
	free(tmp);
	if (*gnl_result)
	{
		run_commandline(*buf_line);
		ft_safe_free_char(buf_line);
	}
	free(line);
}

void	loop_shell(void)
{
	int		gnl_result;
	char	*buf_line;

	gnl_result = 1;
	buf_line = NULL;
	while (TRUE)
	{
		g_interrupted = FALSE;
		g_exited = FALSE;
		set_signal_handler(handle_signal);
		if (gnl_result)
			ft_putstr_fd(SHELL_PROMPT, STDERR_FILENO);
		process_input(&gnl_result, &buf_line);
	}
}

int		main(int argc, char *argv[])
{
	minishell_init();
	if (argc > 2 && ft_strcmp("-c", argv[1]) == 0)
	{
		g_interactive = FALSE;
		run_commandline(argv[2]);
	}
	else
	{
		g_interactive = TRUE;
		loop_shell();
	}
	return (g_status);
}
