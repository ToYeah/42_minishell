/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 21:36:34 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/08 21:36:39 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*casted_pointer;
	unsigned char	casted_char;

	casted_pointer = (unsigned char *)b;
	casted_char = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		casted_pointer[i] = casted_char;
		i++;
	}
	return (b);
}
