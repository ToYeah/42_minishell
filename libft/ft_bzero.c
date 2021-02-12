/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 21:38:02 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/08 21:38:47 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*casted_pointer;

	casted_pointer = (unsigned char *)s;
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			casted_pointer[i] = 0;
			i++;
		}
	}
}
