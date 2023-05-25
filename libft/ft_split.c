/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 03:03:21 by mbachar           #+#    #+#             */
/*   Updated: 2022/11/15 23:51:42 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	words_counter(const char *s, char c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			words++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (words);
}

static char	**free_mem(char **mem)
{
	int	i;

	i = 0;
	while (mem[i])
	{
		free(mem[i]);
		i++;
	}
	free(mem);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t		word_len;
	char		**split;
	size_t		i;

	i = 0;
	if (!s)
		return (NULL);
	split = (char **)malloc((words_counter(s, c) + 1) * sizeof(*split));
	if (!split)
		return (NULL);
	while (*s != '\0')
	{
		while (*s && *s == c)
			s++;
		word_len = 0;
		while (s[word_len] && s[word_len] != c)
			word_len++;
		if (word_len != 0)
			split[i++] = ft_substr(s, 0, word_len);
		if (word_len != 0 && split[i - 1] == 0)
			return (free_mem(split));
		s += word_len;
	}
	split[i] = NULL;
	return (split);
}
