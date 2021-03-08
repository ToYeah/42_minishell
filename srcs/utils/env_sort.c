/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 02:06:44 by nfukada           #+#    #+#             */
/*   Updated: 2021/03/09 02:19:30 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_env	*env_merge(t_env *left, t_env *right, int (*cmp)())
{
	t_env	elem;
	t_env	*next;

	next = &elem;
	while (left != NULL && right != NULL)
	{
		if (cmp(left, right) < 0)
		{
			next->next = left;
			next = next->next;
			left = left->next;
		}
		else
		{
			next->next = right;
			next = next->next;
			right = right->next;
		}
	}
	if (left == NULL)
		next->next = right;
	else
		next->next = left;
	return (elem.next);
}

static t_env	*env_mergesort_sub(t_env *lst, int (*cmp)())
{
	t_env	*left;
	t_env	*right;
	t_env	*right_head;

	if (lst == NULL || lst->next == NULL)
		return (lst);
	left = lst;
	right = lst->next;
	if (right != NULL)
		right = right->next;
	while (right != NULL)
	{
		left = left->next;
		right = right->next;
		if (right != NULL)
			right = right->next;
	}
	right_head = left->next;
	left->next = NULL;
	return (env_merge(env_mergesort_sub(lst, cmp),
		env_mergesort_sub(right_head, cmp), cmp));
}

void			env_mergesort(t_env **lst, int (*cmp)())
{
	*lst = env_mergesort_sub(*lst, cmp);
}
