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

static void	init_here_doc(t_pipex *t, char **line, char **stock, int *tmp_file)
{
	*tmp_file = open("tmp_heredoc", O_WRONLY | O_CREAT | O_APPEND, 0744);
	if (*tmp_file == -1)
		oops_crash(t, "pipex_bonus: error: can't open/create 'tmp_heredoc'\n");
	*line = NULL;
	*stock = NULL;
}

void	create_heredoc(t_pipex *t)
{
	char	*line;
	char	*stock;
	int		tmp_file;

	init_here_doc(t, &line, &stock, &tmp_file);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		if (get_next_line(STDIN_FILENO, &line, &stock) == -1)
			oops_crash(t, "pipex_bonus: error: can't get next line\n");
		if (ft_strncmp(line, t->limiter, ft_strlen(t->limiter)) == FOUND
			&& line[ft_strlen(t->limiter)] == '\0')
		{
			free(line);
			t->infile = open("tmp_heredoc", O_RDONLY);
			if (t->infile == -1)
				oops_crash(t, "pipex_bonus: error: can't open infile\n");
			close(tmp_file);
			free(stock);
			return ;
		}
		ft_putstr_fd(line, tmp_file);
		ft_putstr_fd("\n", tmp_file);
		free(line);
	}
}
