/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 10:35:56 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/28 18:42:40 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

t_env	*get_env(const char *name)
{
	t_env			*now;
	extern t_env	*g_envs;

	if (!g_envs || !name)
		return (NULL);
	now = g_envs;
	while (now)
	{
		if (ft_strncmp(now->name, name, ft_strlen(name) + 1) == 0)
			return (now);
		now = now->next;
	}
	return (NULL);
}
