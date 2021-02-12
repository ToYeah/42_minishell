/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 12:43:29 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/24 00:45:44 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p_dst;
	unsigned char	*p_src;
	unsigned char	search_c;

	p_dst = (unsigned char*)dst;
	p_src = (unsigned char*)src;
	search_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		p_dst[i] = p_src[i];
		if (p_src[i] == search_c)
		{
			return (p_dst + i + 1);
		}
		i++;
	}
	return (NULL);
}
