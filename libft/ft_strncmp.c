/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 22:02:56 by totaisei          #+#    #+#             */
/*   Updated: 2021/01/04 14:18:14 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;

	i = 0;
	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (1)
	{
		if ((casted_s1[i] - casted_s2[i]) != 0)
			return (casted_s1[i] - casted_s2[i]);
		i++;
		if ((!(casted_s1[i]) && !(casted_s2[i])) || i == n)
			break ;
	}
	return (0);
}

int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*casted_s1;
	unsigned char	*casted_s2;

	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	while (*(casted_s1 + 1))
		casted_s1++;
	while (*(casted_s2 + 1))
		casted_s2++;
	while (n > 0)
	{
		if ((*casted_s1 - *casted_s2) != 0)
			return (*casted_s1 - *casted_s2);
		casted_s1--;
		casted_s2--;
		n--;
	}
	return (0);
}
