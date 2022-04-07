/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft_mallocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 01:29:41 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/15 01:29:41 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	i;

	if (s1 == 0 || s2 == 0)
		return (0);
	new_s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_s == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_s[i] = ((char *)s1)[i];
		i++;
	}
	while (*s2)
	{
		new_s[i] = *s2;
		i++;
		s2++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static size_t	slen(unsigned int start, size_t len, size_t size)
{
	if (size < start)
		return (0);
	else if (size - start < len)
		return (size - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;
	size_t	size;

	if (s == 0)
		return (0);
	size = ft_strlen(s);
	new_str = (char *)malloc(sizeof(char) * (slen(start, len, size) + 1));
	if (new_str == 0)
		return (NULL);
	i = 0;
	if (start < size)
	{
		while (s[i + start] && i < len)
		{
			new_str[i] = s[i + start];
			i++;
		}
	}
	new_str[i] = 0;
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	s_len;

	s_len = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (s_len + 1));
	if (str == 0)
		return (NULL);
	ft_strlcpy(str, s, s_len + 1);
	return (str);
}
