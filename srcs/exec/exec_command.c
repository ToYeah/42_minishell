/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 20:16:45 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/27 21:15:07 by nfukada          ###   ########.fr       */
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

static void		ft_free_set(char **dest, char *src)
{
	free(*dest);
	*dest = src;
}

void			exec_command(
	t_command *command, t_pipe_state state, int old_pipe[])
{
	extern t_env	*g_envs;
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
	ft_free_set(&args[0], build_cmd_path(args[0]));
	create_pipe(state, new_pipe);
	if ((pid = fork()) < 0)
		error_exit();
	if (pid == 0)
	{
		dup_pipe(state, old_pipe, new_pipe);
		if (execve(args[0], args, generate_environ(g_envs)) < 0)
			error_exit();
	}
	cleanup_pipe(state, old_pipe, new_pipe);
	command->pid = pid;
	ft_safe_free_split(&args);
}
