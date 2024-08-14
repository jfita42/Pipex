/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:27:00 by jfita             #+#    #+#             */
/*   Updated: 2024/04/30 17:11:36 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	putword(char *word, char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '/';
	word[++i] = '\0';
}

static char	**memalloc(char **array, char const *s, char c)
{
	size_t	len;
	size_t	index;
	size_t	i;

	i = 0;
	index = 0;
	while (s[index])
	{
		len = 0;
		while (s[index + len] && s[index + len] != c)
			len++;
		if (len > 0)
		{
			array[i] = malloc(1 + sizeof(char) * (len + 1));
			if (!array[i])
				return (pipex_free_tab(array), NULL);
			putword(array[i], (s + index), c);
			i++;
			index = index + len;
		}
		else
			index++;
	}
	array[i] = 0;
	return (array);
}

char	**split(char const *s, char c)
{
	size_t	words;
	char	**array;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	array = malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = memalloc(array, s, c);
	if (!array)
		return (NULL);
	return (array);
}
