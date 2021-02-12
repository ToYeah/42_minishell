/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:03:34 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/19 12:12:00 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(unsigned int n, t_bool format, int fd)
{
	if (0 == n)
		write(fd, "0", 1);
	else
	{
		if (n / 16 != 0)
		{
			ft_puthex_fd(n / 16, format, fd);
		}
		if (format == TRUE)
			write(fd, &"0123456789abcdef"[n % 16], 1);
		else
			write(fd, &"0123456789ABCDEF"[n % 16], 1);
	}
}

void	ft_puthex_ul_fd(unsigned long n, t_bool format, int fd)
{
	if (0 == n)
		write(fd, "0", 1);
	else
	{
		if (n / 16 != 0)
		{
			ft_puthex_ul_fd(n / 16, format, fd);
		}
		if (format == TRUE)
			write(fd, &"0123456789abcdef"[n % 16], 1);
		else
			write(fd, &"0123456789ABCDEF"[n % 16], 1);
	}
}
