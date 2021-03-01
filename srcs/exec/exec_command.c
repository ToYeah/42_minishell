/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 20:16:45 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/02 01:13:09 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "const.h"
#include "builtin.h"
#include "exec.h"

static void		exec_binary(char **args)
{
	extern t_env	*g_envs;
	char			**envs;
	char			*path;

	envs = generate_environ(g_envs);
	path = build_cmd_path(args[0]);
	if (path == NULL)
	{
		print_error("command not found", args[0]);
		ft_safe_free_split(&envs);
		exit(STATUS_CMD_NOT_FOUND);
	}
	if (execve(path, args, generate_environ(g_envs)) < 0)
		error_exit(path);
	free(path);
	ft_safe_free_split(&envs);
}

static void		exec_builtin_parent(t_command *command, char **args)
{
	int	stdin;
	int	stdout;
	int	stderr;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	stderr = dup(STDERR_FILENO);
	if (dup_redirects(command) == FALSE)
	{
		close(stdin);
		close(stdout);
		close(stderr);
		return ;
	}
	exec_builtin(args);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	dup2(stderr, STDERR_FILENO);
	close(stdin);
	close(stdout);
	close(stderr);
	return ;
}

static void		exec_command_child(
	t_command *command, char **args, t_pipe_state state, int old_pipe[])
{
	pid_t	pid;
	int		new_pipe[2];

	create_pipe(state, new_pipe);
	if ((pid = fork()) < 0)
		error_exit(NULL);
	if (pid == 0)
	{
		dup_pipe(state, old_pipe, new_pipe);
		if (dup_redirects(command) == FALSE)
			exit(1);
		if (is_builtin(args))
			exit(exec_builtin(args));
		else
			exec_binary(args);
	}
	cleanup_pipe(state, old_pipe, new_pipe);
	command->pid = pid;
}

static void		update_pipe_state(t_command *command, t_pipe_state *state)
{
	if (*state == NO_PIPE)
		return ;
	if (command->next)
		*state = PIPE_READ_WRITE;
	else
		*state = PIPE_READ_ONLY;
}

void			exec_command(
	t_command *command, t_pipe_state *state, int old_pipe[])
{
	char			**args;

	if (setup_redirects(command) == FALSE)
		return ;
	if (convert_tokens(command, &args) == FALSE)
	{
		cleanup_redirects(command);
		return ;
	}
	if (*state == NO_PIPE && is_builtin(args))
		exec_builtin_parent(command, args);
	else
		exec_command_child(command, args, *state, old_pipe);
	update_pipe_state(command, state);
	ft_safe_free_split(&args);
}
