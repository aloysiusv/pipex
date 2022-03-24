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

typedef struct s_child	t_child;
typedef struct s_pipex	t_pipex;

struct s_child
{
	int			fd[2];
	int			pid;
	char		**command;
	char		**all_paths;
	char		*full_path;
	t_child		*prev_child;
	t_child		*next_child;
};

struct s_pipex
{
	size_t		argc;
	char		**argv;
	char		**envp;
	int			infile;
	int			outfile;
	size_t		nb_cmds;
	size_t		current_cmd;
	int			heredoc;
	char		*limiter;
	t_child		*head_child;
};

// enum e_fd
// {
// 	IN,
// 	OUT,
// 	MAX_FD,
// };
// struct s_tmp
// {
// 	char *cmd;
// 	int	pid;
// 	int fd[MAX_FD];// fd[IN] = 0;fd[OUT] = 1;
// 	char **env;// maybe not sure
// 	struct s_tmp *next;// NULL
// };

// while (s_tmp)
// {
// 	if (s_tmp->next)
// 	{
// 		// call a function for pipe
// 		FD[OUT] = pip_ret_in;
// 		s_tmp->next->fd[IN] = pip_ret_out;
// 	}
// 	if (redirection)// give up pas a faire

// 	fork + execve

// 	close(fd);//all fd
// 	s_tmp = s_tmp->next;
// }

// while (s_tmp)
// 	waitpid(s_tmp->pid);

void	start_master_process(t_pipex *t);
void	create_heredoc(t_pipex *t);
void	redir_exec(t_pipex *t);
void	execute_command(t_pipex *t);

t_child	*add_next_child(t_child *current_child);
void	delete_children(t_pipex *t);

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

#endif
