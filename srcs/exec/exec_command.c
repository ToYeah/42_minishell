/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 20:16:45 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/27 23:04:27 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "expander.h"

static t_bool	convert_tokens(t_command *command, char ***args)
{
	expand_tokens(&command->args);
	*args = convert_args(command);
	if (*args[0] == NULL)
		return (FALSE);
	return (TRUE);
}

static void		exec_binary(
	char **args, t_pipe_state state, int old_pipe[], int new_pipe[])
{
	extern t_env	*g_envs;
	char			**envs;
	char			*path;

	dup_pipe(state, old_pipe, new_pipe);
	envs = generate_environ(g_envs);
	path = build_cmd_path(args[0]);
	if (path == NULL)
	{
		print_error("command not found", args[0]);
	}
	if (execve(path, args, generate_environ(g_envs)) < 0)
		error_exit();
	free(path);
	ft_safe_free_split(&envs);
}

void			exec_command(
	t_command *command, t_pipe_state state, int old_pipe[])
{
	pid_t			pid;
	char			**args;
	int				new_pipe[2];

	if (convert_tokens(command, &args) == FALSE)
		return ;
	if (is_builtin(args))
	{
		exec_builtin(args);
		return ;
	}
	create_pipe(state, new_pipe);
	if ((pid = fork()) < 0)
		error_exit();
	if (pid == 0)
		exec_binary(args, state, old_pipe, new_pipe);
	cleanup_pipe(state, old_pipe, new_pipe);
	command->pid = pid;
	ft_safe_free_split(&args);
}
