/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_through.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:15:36 by totaisei          #+#    #+#             */
/*   Updated: 2021/01/04 14:19:48 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_through_space(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str == ' ')
		str++;
	return (str);
}

char	*ft_through_digit(char *str)
{
	if (!str)
		return (NULL);
	while (*str && ft_isdigit(*str))
		str++;
	return (str);
}
