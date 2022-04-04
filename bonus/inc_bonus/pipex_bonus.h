/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 08:06:58 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/22 08:06:58 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

# define IN		0
# define OUT	1

# define FOUND	0

# define NO		0
# define YES	1

typedef struct s_pipex
{
	size_t		argc;
	char		**argv;
	char		**envp;
	int			infile;
	int			outfile;
	int			*fd_pipes;
	size_t		nb_fds;
	size_t		nb_cmds;
	size_t		index;
	size_t		current_cmd;
	char		**command;
	char		**all_paths;
	char		*full_path;
	int			heredoc;
	char		*limiter;
}				t_pipex;

void	start_parent_process(t_pipex *t);
void	create_heredoc(t_pipex *t);
void	redir_exec(t_pipex *t);
void	execute_command(t_pipex *t);

void	open_pipes(t_pipex *t);
void	close_pipes(t_pipex *t);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const	char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		get_next_line(int fd, char **line);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);

void	oops_crash(t_pipex *t, char *error_message);
void	free_all(t_pipex *t);

#endif
