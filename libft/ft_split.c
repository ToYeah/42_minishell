/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfukada <nfukada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:02:33 by nfukada           #+#    #+#             */
/*   Updated: 2020/06/28 11:20:30 by nfukada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int i;
	int len;

	if (str[0] == '\0')
	{
		return (0);
	}
	len = 1;
	if (str[0] == c)
	{
		len = 0;
	}
	i = 1;
	while (str[i])
	{
		if (str[i - 1] == c && str[i] != c)
		{
			len++;
		}
		i++;
	}
	return (len);
}

static int	count_word(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		i++;
	}
	return (i);
}

static void	free_all_words(char **words, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static char	**set_words(char const *s, char c, char **words, int words_len)
{
	int	i;
	int	word_len;

	i = 0;
	while (i < words_len)
	{
		while (*s == c && *s != '\0')
		{
			s++;
		}
		word_len = count_word(s, c);
		words[i] = (char *)malloc((word_len + 1) * sizeof(char));
		if (words[i] == NULL)
		{
			free_all_words(words, i);
			return (NULL);
		}
		ft_strlcpy(words[i], s, word_len + 1);
		s += word_len;
		i++;
	}
	words[i] = 0;
	return (words);
}

char		**ft_split(char const *s, char c)
{
	char	**words;
	int		words_len;

	if (s == NULL)
	{
		return (NULL);
	}
	words_len = count_words(s, c);
	words = (char **)malloc((words_len + 1) * sizeof(char *));
	if (words == NULL)
	{
		return (NULL);
	}
	return (set_words(s, c, words, words_len));
}
