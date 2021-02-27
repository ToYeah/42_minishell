/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 17:08:55 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/27 23:29:46 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**convert_args(t_command *command)
{
	char	**args;
	t_token	*now_token;
	size_t	len;
	size_t	i;

	len = 0;
	now_token = command->args;
	while (now_token)
	{
		now_token = now_token->next;
		len++;
	}
	if (!(args = (char **)malloc(sizeof(char *) * (len + 1))))
		error_exit(NULL);
	now_token = command->args;
	i = 0;
	while (now_token)
	{
		if (!(args[i] = ft_strdup(now_token->data)))
			error_exit(NULL);
		now_token = now_token->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}
