/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 12:43:33 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/23 19:18:35 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	search_c;
	unsigned char	*p_s;

	search_c = (unsigned char)c;
	p_s = (unsigned char*)s;
	while (n--)
	{
		if (*p_s == search_c)
		{
			return (p_s);
		}
		p_s++;
	}
	return (NULL);
}
