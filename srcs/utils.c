/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 03:11:16 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/11 03:11:16 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0)
		return ;
	write(fd, s, ft_strlen(s));
}

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

size_t	ft_strlcpy(char *dst, const	char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

void	free_all(t_pipex *t)
{
	// size_t	i;

	// i = 0;
	// while (t->bin_path[i])
	// {
	// 	free(&t->bin_path[i]);
	// 	i++;
	// }
	// i = 0;
	// if (t->command)
	// {
	// 	while (t->command[i])
	// 	{
	// 		free(&t->command[i]);
	// 		i++;
	// 	}
	// 	free(t->command);
	// }
	if (t->pipes)
		free(t->pipes);
	if (t)
		free(t);
}
