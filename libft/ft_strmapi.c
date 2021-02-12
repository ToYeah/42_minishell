/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:02:45 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/24 14:41:51 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len_s;
	size_t	i;
	char	*mapped;

	if (s == NULL)
	{
		return (NULL);
	}
	len_s = ft_strlen(s);
	i = 0;
	mapped = (char *)malloc(sizeof(char) * (len_s + 1));
	if (mapped == NULL)
	{
		return (NULL);
	}
	while (i < len_s)
	{
		mapped[i] = f(i, s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
