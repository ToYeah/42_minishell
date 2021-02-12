/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 12:44:16 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/22 19:36:46 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen(s);
	if (c == '\0')
	{
		return ((char *)(s + len));
	}
	while (len--)
	{
		if (s[len] == c)
		{
			return ((char *)(s + len));
		}
	}
	return (NULL);
}
