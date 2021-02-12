/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 23:48:03 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/10 13:52:26 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	byte_size;

	byte_size = (count == 0 || size == 0) ? 1 : count * size;
	res = malloc(byte_size);
	if (!res)
		return (NULL);
	ft_bzero(res, byte_size);
	return (res);
}
