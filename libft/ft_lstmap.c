/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:37:50 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/24 17:58:07 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_first;
	t_list	*lst_new;

	lst_first = NULL;
	while (lst)
	{
		lst_new = ft_lstnew(f(lst->content));
		if (lst_new == NULL)
		{
			if (lst_first != NULL)
			{
				ft_lstclear(&lst_first, del);
			}
			return (NULL);
		}
		ft_lstadd_back(&lst_first, lst_new);
		lst = lst->next;
	}
	return (lst_first);
}
