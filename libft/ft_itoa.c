/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 22:47:54 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/19 12:21:17 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*zero_itoa(void)
{
	char *res;

	if (!(res = malloc(sizeof(char) * 2)))
		return (NULL);
	res[0] = '0';
	res[1] = '\0';
	return (res);
}

static char		*setup_sign_null(int digit, int sign)
{
	char *res;

	if (!(res = malloc(sizeof(char) * digit + 1 + (sign * -1))))
		return (NULL);
	res[digit + (sign * -1)] = '\0';
	if (sign)
		res[0] = '-';
	return (res);
}

char			*ft_itoa(int n)
{
	int		digit;
	int		sign;
	int		i;
	long	tmp;
	char	*res;

	sign = 0;
	if (n == 0)
		return (zero_itoa());
	if (n < 0)
		sign = -1;
	digit = ft_nbrdig(n);
	if (!(res = setup_sign_null(digit, sign)))
		return (NULL);
	i = digit + (sign * -1) - 1;
	tmp = n;
	if (sign)
		tmp *= -1;
	while (tmp > 0)
	{
		res[i--] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	return (res);
}
