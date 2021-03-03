/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonicalisation.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:55:58 by totaisei          #+#    #+#             */
/*   Updated: 2021/03/03 16:03:55 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANONICALISATION_H
# define CANONICALISATION_H

typedef struct s_canon_list	t_canon_list;

struct	s_canon_list
{
	char			*data;
	t_canon_list	*next;
	t_canon_list	*prev;
};

void	del_canonlist(t_canon_list **list);
void	remove_canon(t_canon_list *list, t_canon_list **start);

#endif
