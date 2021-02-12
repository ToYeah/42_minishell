/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 12:43:43 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/23 20:52:13 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	if (dst == NULL && src == NULL)
	{
		return (dst);
	}
	if (p_dst < p_src)
	{
		while (len--)
		{
			*p_dst++ = *p_src++;
		}
	}
	else
	{
		while (len--)
		{
			*(p_dst + len) = *(p_src + len);
		}
	}
	return (dst);
}
