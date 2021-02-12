/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:03:05 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/24 00:35:59 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_numbers(int n, int fd)
{
	if (n / 10 == 0)
	{
		if (n < 0)
		{
			ft_putchar_fd('0' - n % 10, fd);
		}
		else
		{
			ft_putchar_fd('0' + n % 10, fd);
		}
	}
	else
	{
		put_numbers(n / 10, fd);
		put_numbers(n % 10, fd);
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
	}
	put_numbers(n, fd);
}
