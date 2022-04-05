/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:21:24 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/12 14:21:24 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	*free_words(char **new_arr, size_t nb_of_words)
{
	size_t	i;

	i = 0;
	while (i < nb_of_words)
		free(new_arr[i++]);
	free(new_arr);
	return (NULL);
}

static size_t	word_count(char const *s, char sep)
{
	size_t	i;
	size_t	nb_of_words;

	i = 0;
	nb_of_words = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i] != '\0')
			nb_of_words++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (nb_of_words);
}

static char	*word_cpy(char const **s, char sep)
{
	char	*word;
	size_t	i;

	i = 0;
	while (**s && (*s)[i] == sep)
		(*s)++;
	while ((*s)[i] && (*s)[i] != sep)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == 0)
		return (0);
	ft_strlcpy(word, *s, i + 1);
	*s = *s + i;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**new_arr;
	size_t	size;
	size_t	i;

	if (s == NULL)
		return (NULL);
	size = word_count(s, c);
	new_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (new_arr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_arr[i] = word_cpy(&s, c);
		if (new_arr[i] == NULL)
			return (free_words(new_arr, size));
		i++;
	}
	new_arr[i] = '\0';
	return (new_arr);
}
