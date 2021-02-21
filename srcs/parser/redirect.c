/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 13:24:58 by nfukada           #+#    #+#             */
/*   Updated: 2021/02/21 14:02:49 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void		add_redirect(t_redirect **list, t_redirect *new)
{
	t_redirect	*now;

	if (!*list)
		*list = new;
	else
	{
		now = *list;
		while (now->next)
			now = now->next;
		now->next = new;
		new->next = NULL;
	}
}

t_redirect	*create_redirect(void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redirect)
	{
		error_exit();
	}
	redirect->fd = -1;
	redirect->next = NULL;
	redirect->filename = NULL;
	return (redirect);
}
