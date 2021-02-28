/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 12:27:41 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/28 16:47:14 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	ov_div;
	unsigned long	result;

	i = 0;
	result = 0;
	ov_div = MY_LONG_MAX / 10;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	sign = str[i] == '-' ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		if ((ov_div < result || (ov_div == result && str[i] > '7'))
		&& sign == 1)
			return ((int)MY_LONG_MAX);
		else if ((ov_div < result || (ov_div == result && str[i] > '8'))
		&& sign == -1)
			return ((int)(MY_LONG_MAX * -1 - 1));
		result *= 10;
		result += str[i++] - '0';
	}
	return ((int)result * sign);
}

t_bool		ft_atoi_limit(const char *str, int *return_value)
{
	int				i;
	int				sign;
	unsigned long	div;
	unsigned long	res;

	i = 0;
	res = 0;
	div = INT_MAX / 10;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	sign = str[i] == '-' ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		if ((div < res || (div == res && str[i] > '7')) && sign == 1)
			return (FALSE);
		else if ((div < res || (div == res && str[i] > '8'))
		&& sign == -1)
			return (FALSE);
		res *= 10;
		res += str[i++] - '0';
	}
	*return_value = (int)res * sign;
	return (TRUE);
}

int			ft_atoi_overflow_zero(const char *str)
{
	int				i;
	int				sign;
	unsigned long	ov_div;
	unsigned long	result;

	i = 0;
	result = 0;
	ov_div = MY_LONG_MAX / 10;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	sign = str[i] == '-' ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ('0' <= str[i] && str[i] <= '9'))
	{
		if ((ov_div < result || (ov_div == result && str[i] > '7'))
		&& sign == 1)
			return (0);
		else if ((ov_div < result || (ov_div == result && str[i] > '8'))
		&& sign == -1)
			return (0);
		result *= 10;
		result += str[i++] - '0';
	}
	return ((int)result * sign);
}