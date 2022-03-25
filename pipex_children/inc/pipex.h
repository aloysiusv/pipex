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
# include <sys/types.h>
# include <fcntl.h>
# include <stdio.h>

# define IN	0
# define OUT	1

# define FOUND		0
# define NOT_FOUND -1

typedef struct s_pipex
{
	size_t		argc;
	char		**argv;
	char		**envp;
	int			infile;
	int			outfile;
	int			fd[2];
	size_t		nb_cmds;
	size_t		current_cmd;
	char		**command;
	char		**all_paths;
	char		*full_path;
}				t_pipex;

void	execute_command(t_pipex *t);
void	redir_exec(t_pipex *t);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const	char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);

void	oops_crash(t_pipex *t, char *error_message);

#endif
