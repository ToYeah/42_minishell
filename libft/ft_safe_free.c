/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 18:58:20 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/24 10:56:50 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_safe_free_char(char **target)
{
	free(*target);
	*target = NULL;
}

void	ft_safe_free_split(char ***target)
{
	size_t index;

	index = 0;
	if (!*target)
		return ;
	while ((*target)[index])
	{
		free((*target)[index]);
		(*target)[index] = NULL;
		index++;
	}
	free(*target);
	*target = NULL;
}