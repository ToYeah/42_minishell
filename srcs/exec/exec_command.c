/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 20:16:45 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/08 18:12:20 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <signal.h>
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
	if (execve(path, args, generate_environ(g_envs)) < 0)
	{
		if (errno == ENOEXEC)
			exit(EXIT_SUCCESS);
		print_error(strerror(errno), path);
		if (errno == ENOENT)
			exit(STATUS_CMD_NOT_FOUND);
		else
			exit(STATUS_CMD_NOT_EXECUTABLE);
	}
	free(path);
	ft_safe_free_split(&envs);
}

static int		exec_builtin_parent(t_command *command, char **args)
{
	if (setup_redirects(command) == FALSE)
		return (EXIT_FAILURE);
	if (dup_redirects(command, TRUE) == FALSE)
		return (EXIT_FAILURE);
	return (exec_builtin(args));
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
		set_signal_handler(SIG_DFL);
		if (setup_redirects(command) == FALSE)
			exit(EXIT_FAILURE);
		if (args[0] == NULL)
			exit(EXIT_SUCCESS);
		dup_pipe(state, old_pipe, new_pipe);
		if (dup_redirects(command, FALSE) == FALSE)
			exit(EXIT_FAILURE);
		if (is_builtin(args))
			exit(exec_builtin(args));
		else
			exec_binary(args);
	}
	set_signal_handler(SIG_IGN);
	cleanup_pipe(state, old_pipe, new_pipe);
	command->pid = pid;
}

static void		update_pipe_state(t_command *command, t_pipe_state *state)
{
	if (*state == NO_PIPE)
		return ;
	if (command->next && command->next->next)
		*state = PIPE_READ_WRITE;
	else
		*state = PIPE_READ_ONLY;
}

int				exec_command(
	t_command *command, t_pipe_state *state, int old_pipe[])
{
	char	**args;
	int		status;

	status = EXIT_SUCCESS;
	convert_tokens(command, &args);
	if (*state == NO_PIPE && is_builtin(args))
		status = exec_builtin_parent(command, args);
	else
		exec_command_child(command, args, *state, old_pipe);
	cleanup_redirects(command);
	update_pipe_state(command, state);
	ft_safe_free_split(&args);
	return (status);
}
