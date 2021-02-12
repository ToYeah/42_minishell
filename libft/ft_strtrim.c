/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 15:23:48 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/14 20:56:51 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_set(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	const char	*start;
	char		*res;
	size_t		len;
	size_t		i;
	size_t		j;

	if (!(s1) || !(set))
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (is_set(s1[i], set) && s1[i])
		i++;
	if (len == i)
		return (ft_strdup("\0"));
	start = &s1[i];
	j = len - 1;
	while (is_set(s1[j], set) && s1[j])
		j--;
	if (!(res = malloc(sizeof(char) * (j - i + 2))))
		return (NULL);
	ft_strlcpy(res, start, j - i + 2);
	return (res);
}
