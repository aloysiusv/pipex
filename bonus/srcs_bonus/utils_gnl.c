/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 08:20:18 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/22 08:20:18 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static size_t	ft_strclen(char *buf, char c)
{
	size_t	i;

	i = 0;
	while (buf[i] != 0 && buf[i] != c)
		i++;
	return (i);
}

static char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

static int	read_file(int fd, char **stock)
{
	char	buf[1024 + 1];
	int		nbytes;
	char	*tmp;

	nbytes = 1;
	while (nbytes != 0)
	{
		nbytes = read(fd, buf, 1024);
		if (nbytes == -1)
			return (-1);
		buf[nbytes] = 0;
		if (*stock == 0)
			*stock = ft_strdup(buf);
		else
		{
			tmp = *stock;
			*stock = ft_strjoin(tmp, buf);
			free(tmp);
		}
		if (*stock == NULL)
			return (-1);
		if (ft_strchr(*stock, '\n') != 0)
			break ;
	}
	return (1);
}

static int	create_one_line(char **line, char **stock)
{
	char	*tmp;
	size_t	line_size;

	if (ft_strchr(*stock, '\n') == 0)
	{
		*line = ft_strdup(*stock);
		free(*stock);
		*stock = 0;
		if (*line == NULL)
			return (-1);
		return (0);
	}
	else
	{
		line_size = ft_strclen(*stock, '\n');
		*line = ft_substr(*stock, 0, line_size);
		tmp = *stock;
		*stock = ft_strdup(tmp + line_size + 1);
		free(tmp);
		if (*line == NULL || *stock == NULL)
			return (-1);
	}
	return (1);
}

int	get_next_line(int fd, char **line, char **stock)
{
	int				read_status;

	read_status = read_file(fd, stock);
	if (read_status == -1 || !line)
		return (-1);
	if (read_status == 0 && stock == 0)
	{
		*line = ft_strdup("");
		if (*line == NULL)
			return (-1);
		return (0);
	}
	return (create_one_line(line, stock));
}
