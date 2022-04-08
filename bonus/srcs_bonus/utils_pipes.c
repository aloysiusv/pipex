/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:46:18 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/31 15:46:18 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

void	open_pipes(t_pipex *t)
{
	size_t	i;

	t->nb_fds = 2 * (t->nb_cmds - 1);
	t->fd_pipes = (int *)malloc(sizeof(int) * t->nb_fds);
	if (t->fd_pipes == NULL)
		oops_crash(t, "pipex_bonus: error: couldn't create pipes\n");
	i = 0;
	while (i < (t->nb_cmds - 1))
	{
		if (pipe(&t->fd_pipes[2 * i]) < 0)
			oops_crash(t, "pipex_bonus: error: couldn't open pipes\n");
		i++;
	}
}

void	close_pipes(t_pipex *t)
{
	size_t	i;

	i = 0;
	while (i < t->nb_fds)
	{
		close(t->fd_pipes[i]);
		i++;
	}
}
