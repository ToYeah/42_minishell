/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 21:59:03 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/09 23:29:08 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (i < len)
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			res = (char *)&haystack[i];
			while (res[j] == needle[j] && i + j < len && res[j])
				j++;
			if (needle[j] == '\0')
				return (res);
		}
		i++;
	}
	return (NULL);
}
