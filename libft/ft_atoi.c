/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 12:22:31 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/25 19:56:16 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_is_sign(const char c)
{
	if (c == '+')
	{
		return (1);
	}
	if (c == '-')
	{
		return (-1);
	}
	return (0);
}

static int	char_is_space(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
	{
		return (1);
	}
	return (0);
}

static int	get_int(const char *str, int sign)
{
	int				i;
	unsigned long	num;
	unsigned long	ov_div;
	int				ov_mod;

	i = 0;
	num = 0;
	ov_div = LONG_MAX / 10;
	ov_mod = LONG_MAX % 10;
	if (sign == -1)
		ov_mod++;
	while (ft_isdigit(str[i]))
	{
		if (num > ov_div || (num == ov_div && str[i] - '0' > ov_mod))
		{
			if (sign == 1)
				return ((int)LONG_MAX);
			return ((int)LONG_MIN);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(num * sign));
}

int			ft_atoi(const char *str)
{
	int	sign;
	int	i;

	i = 0;
	while (char_is_space(str[i]))
	{
		i++;
	}
	sign = char_is_sign(str[i]);
	if (sign)
	{
		i++;
	}
	else
	{
		sign = 1;
	}
	return (get_int(str + i, sign));
}
