/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:03:39 by totaisei          #+#    #+#             */
/*   Updated: 2021/02/27 23:28:22 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "utils.h"
#include "libft.h"

size_t	calc_escaped_value_len(const char *str, const char *esc)
{
	size_t index;
	size_t res;

	index = 0;
	res = 0;
	while (str[index] != 0)
	{
		if (ft_strchr(esc, str[index]) != NULL)
			res++;
		res++;
		index++;
	}
	return (res);
}

void	copy_escaped_value(const char *src, const char *esc, char *dest)
{
	size_t res_index;
	size_t index;

	index = 0;
	res_index = 0;
	while (src[index] != 0)
	{
		if (ft_strchr(esc, src[index]) != NULL)
		{
			dest[res_index] = '\\';
			res_index++;
		}
		dest[res_index] = src[index];
		res_index++;
		index++;
	}
	dest[res_index] = '\0';
}

char	*create_expanded_str(const char *str, t_token_state state)
{
	char *esc_chars;
	char *res;

	esc_chars = "\"\\$";
	if (state == STATE_GENERAL)
		esc_chars = "\'\"\\$|;><";
	if (!(res = malloc(sizeof(char *) *
		(calc_escaped_value_len(str, esc_chars) + 1))))
		error_exit(NULL);
	copy_escaped_value(str, esc_chars, res);
	return (res);
}
