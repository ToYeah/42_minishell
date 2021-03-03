/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_canonicalisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 12:09:25 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/03 16:03:07 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include "canonicalisation.h"

t_canon_list	*set_canonlist(char **split)
{
	t_canon_list	*res;
	t_canon_list	*prev;
	t_canon_list	*now;
	size_t			index;

	prev = NULL;
	res = NULL;
	index = 0;
	while (split[index])
	{
		if (!(now = malloc(sizeof(t_canon_list))))
			error_exit(NULL);
		if (!res)
			res = now;
		now->data = split[index];
		now->prev = prev;
		now->next = NULL;
		if (prev)
			prev->next = now;
		prev = now;
		index++;
	}
	return (res);
}

t_canon_list	*create_canonical_list(char **split)
{
	t_canon_list *now;
	t_canon_list *res;
	t_canon_list *tmp;

	res = set_canonlist(split);
	now = res;
	while (now)
	{
		if (ft_strcmp(now->data, ".") == 0)
		{
			tmp = now;
			now = now->next;
			remove_canon(tmp, &res);
		}
		else if (ft_strcmp(now->data, "..") == 0)
		{
			tmp = now;
			now = now->next;
			remove_canon(tmp->prev, &res);
			remove_canon(tmp, &res);
		}
		else
			now = now->next;
	}
	return (res);
}

char			*ft_strcpy_forward(char *dest, char *src)
{
	size_t index;

	index = 0;
	while (src[index])
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (&(dest[index]));
}

void			cpy_canonical_path(char **res, t_canon_list *list)
{
	char *str;

	str = *res;
	while (list)
	{
		*str = '/';
		str++;
		str = ft_strcpy_forward(str, list->data);
		list = list->next;
	}
	if (str == *res)
	{
		*str = '/';
		str++;
	}
	*str = '\0';
}

char			*path_canonicalisation(char *path)
{
	char			**split;
	char			*res;
	t_canon_list	*list;

	if (!path)
		return (NULL);
	if (!(split = ft_split(path, '/')) ||
		!(res = malloc(sizeof(char *) * (ft_strlen(path) + 1))))
		error_exit(NULL);
	list = create_canonical_list(split);
	cpy_canonical_path(&res, list);
	del_canonlist(&list);
	ft_safe_free_split(&split);
	return (res);
}
