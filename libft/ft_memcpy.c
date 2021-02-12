/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 21:29:02 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/08 21:39:55 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*casted_dest;
	unsigned char	*casted_src;

	if (dst == src)
		return (dst);
	casted_dest = (unsigned char *)dst;
	casted_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		casted_dest[i] = casted_src[i];
		i++;
	}
	return (dst);
}
