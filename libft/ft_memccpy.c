/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:48:51 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/08 21:45:14 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*casted_dest;
	unsigned char	*casted_src;

	casted_dest = (unsigned char *)dst;
	casted_src = (unsigned char *)src;
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			casted_dest[i] = casted_src[i];
			if (casted_src[i] == (unsigned char)c)
				return ((void *)(&casted_dest[++i]));
			i++;
		}
	}
	return (NULL);
}
