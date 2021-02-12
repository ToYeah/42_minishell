/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrdig.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:18:29 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/19 12:37:22 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_nbrdig(int n)
{
	int		res;
	long	tmp;

	res = 0;
	tmp = n;
	if (tmp == 0)
		return (1);
	if (tmp < 0)
		tmp *= -1;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		res++;
	}
	return (res);
}

int	ft_nbrdig_ui(unsigned int n)
{
	int		res;
	long	tmp;

	res = 0;
	tmp = n;
	if (tmp == 0)
		return (1);
	while (tmp > 0)
	{
		tmp = tmp / 10;
		res++;
	}
	return (res);
}

int	ft_nbrdig_hex(unsigned int n)
{
	int		res;

	res = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		res++;
	}
	return (res);
}

int	ft_nbrdig_hex_ul(unsigned long n)
{
	int		res;

	res = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		res++;
	}
	return (res);
}
