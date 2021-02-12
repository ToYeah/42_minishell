/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:02:02 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/24 00:45:09 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_n_len(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		len++;
	}
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		sign;

	len = get_n_len(n);
	str = (char *)malloc(len + 1);
	if (str == NULL)
	{
		return (NULL);
	}
	sign = 1;
	if (n < 0)
		sign = -1;
	str[len] = '\0';
	while (len--)
	{
		str[len] = n % 10 * sign + '0';
		n /= 10;
	}
	if (sign < 0)
	{
		str[0] = '-';
	}
	return (str);
}
