/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 17:23:32 by mbachar           #+#    #+#             */
/*   Updated: 2023/08/05 20:13:01 by mbachar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	words_counter(char *s, char *c)
{
	int		i;
	int		words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr2(c, s[i]))
			i++;
		else
		{
			words++;
			while (s[i] != '\0' && !ft_strchr2(c, s[i]))
				i++;
		}
	}
	return (words);
}

static char	**free_mem2(char **mem)
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

char	**ft_split2(char *s, char *c)
{
	size_t		word_len;
	char		**split;
	size_t		i;

	i = 0;
	if (!s || !c)
		return (NULL);
	split = (char **)malloc((words_counter(s, c) + 1) * sizeof(*split));
	if (!split)
		return (free(split), NULL);
	while (*s != '\0')
	{
		while (*s && ft_strchr2(c, *s))
			s++;
		word_len = 0;
		while (s[word_len] && !ft_strchr2(c, s[word_len]))
			word_len++;
		if (word_len != 0)
			split[i++] = ft_substr(s, 0, word_len);
		if (word_len != 0 && split[i - 1] == 0)
			return (free_mem2(split));
		s += word_len;
	}
	split[i] = NULL;
	return (split);
}
