/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_canonicalisation_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:00:52 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/03 16:02:19 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canonicalisation.h"
#include <stdlib.h>

void	del_canonlist(t_canon_list **list)
{
	t_canon_list *tmp;
	t_canon_list *now;

	if (!list || !*list)
		return ;
	now = *list;
	while (now)
	{
		tmp = now;
		now = now->next;
		free(tmp);
		tmp = NULL;
	}
	*list = NULL;
}

void	remove_canon(t_canon_list *list, t_canon_list **start)
{
	if (!list)
	{
		return ;
	}
	if (list->next)
	{
		list->next->prev = list->prev;
	}
	if (list->prev)
	{
		list->prev->next = list->next;
	}
	else
	{
		*start = list->next;
	}
	free(list);
}
