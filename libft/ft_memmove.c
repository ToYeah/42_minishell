/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 21:40:53 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/14 21:22:17 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*casted_dest;
	unsigned char	*casted_src;

	if (dst == src || len == 0)
		return (dst);
	casted_dest = (unsigned char *)dst;
	casted_src = (unsigned char *)src;
	if (casted_src < casted_dest)
	{
		i = len;
		while (i-- > 0)
			casted_dest[i] = casted_src[i];
	}
	else
	{
		i = 0;
		while (i < len)
		{
			casted_dest[i] = casted_src[i];
			i++;
		}
	}
	return (dst);
}
