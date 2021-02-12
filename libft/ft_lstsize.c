/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:12:06 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/11 23:20:35 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		res;
	t_list	*target;

	if (!lst)
		return (0);
	res = 0;
	target = lst;
	while (target != NULL)
	{
		target = target->next;
		res++;
	}
	return (res);
}
