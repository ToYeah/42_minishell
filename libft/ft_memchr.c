/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 21:47:49 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/08 21:48:15 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*casted_s;

	casted_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (casted_s[i] == (unsigned char)c)
			return ((void *)(&casted_s[i]));
		i++;
	}
	return (NULL);
}
