/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.5_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:47:19 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/21 19:47:19 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	write_line(t_pipex *t, int *fd_heredoc)
{
	char	*line;
	size_t	lim_len;

	lim_len = ft_strlen(t->limiter);
	while (1)
	{
		ft_putstr_fd("pipex here_doc> ", STDOUT_FILENO);
		if (get_next_line(STDIN_FILENO, &line) == -1)
			oops_crash(t, "Error: failed to retrieve line\n");
		if (ft_strncmp(line, t->limiter, lim_len) == FOUND)
		{
			free(line);
			return ;
		}
		ft_putstr_fd(line, fd_heredoc[WRITE]);
		ft_putstr_fd("\n", fd_heredoc[WRITE]);
		free(line);
	}
}

void	create_heredoc(t_pipex *t)
{
	pid_t	pid;
	int		fd_heredoc[2];

	if (pipe(fd_heredoc) == -1)
		oops_crash(t, "Error: 'pipe' failed in here_doc\n");
	pid = fork();
	if (pid == -1)
		oops_crash(t, "Error: 'fork' failed in here_doc\n");
	if (pid == 0)
		write_line(t, fd_heredoc);
	dup2(fd_heredoc[READ], STDIN_FILENO);
	close(fd_heredoc[READ]);
	close(fd_heredoc[WRITE]);
}
