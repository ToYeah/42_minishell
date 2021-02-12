/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 12:53:58 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/10 16:56:16 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			char_count;
	size_t			i;

	if (!s)
		return (NULL);
	if (len == 0 || start > ft_strlen(s))
	{
		if (!(res = malloc(sizeof(char))))
			return (NULL);
		*res = '\0';
		return (res);
	}
	char_count = ft_strlen(&s[start]) > len ? len : ft_strlen(&s[start]);
	if (!(res = malloc(sizeof(char) * (char_count + 1))))
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
