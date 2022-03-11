/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:42:12 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/11 00:42:12 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

# define STDIN			0
# define STDOUT			1
# define STDERR			2

typedef struct	s_pipex
{
	int			infile;
    int			outfile;
	int			**pipes;
	size_t		nb_commands;
	size_t		nb_pipes;
	size_t		cmd_pos;
	char		**command;
	char		*bin_path[5];
}				t_pipex;

void	open_pipes(t_pipex *t);
void	close_pipes(t_pipex *t);
int		execute_command(t_pipex *t, char *argv[]);
void	make_slaves(t_pipex *t, char *argv[]);

char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const	char *src, size_t size);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);

void	free_all(t_pipex *t);

#endif
