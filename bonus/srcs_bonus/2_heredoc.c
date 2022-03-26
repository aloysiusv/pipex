/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_heredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:23:51 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/22 09:23:51 by lrandria         ###   ########.fr       */
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
		ft_putstr_fd("> ", STDOUT_FILENO);
		if (get_next_line(STDIN_FILENO, &line) == -1)
			oops_crash(t, "error: invalid input\n");
		if (ft_strncmp(line, t->limiter, lim_len) == FOUND)
		{
			free(line);
			return ;
		}
		ft_putstr_fd(line, fd_heredoc[OUT]);
		ft_putstr_fd("\n", fd_heredoc[OUT]);
		free(line);
	}
}

void	create_heredoc(t_pipex *t)
{
	pid_t	pid;
	int		fd_heredoc[2];

	if (pipe(fd_heredoc) == -1)
		oops_crash(t, "pipex: error: 'pipe' failed in heredoc\n");
	pid = fork();
	if (pid == -1)
		oops_crash(t, "pipex: error: 'fork' failed in heredoc\n");
	if (pid == 0)
		write_line(t, fd_heredoc);
	dup2(fd_heredoc[IN], STDIN_FILENO);
	close(fd_heredoc[IN]);
	close(fd_heredoc[OUT]);
}
