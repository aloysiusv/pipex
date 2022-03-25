/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:13:58 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/21 20:13:58 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	close_all_fds(t_pipex *t)
{
	size_t	i;

	while (i < t->nb_cmds)
	{
		close(t->head_child->fd[IN]);
		close(t->head_child->fd[OUT]);
		t->head_child = t->head_child->next_child;
		i++;
	}
	t->head_child = t->head_child->next_child;
}

void	start_master_process(t_pipex *t)
{
	t->current_cmd = 2;
	if (t->heredoc == YES)
	{
		t->current_cmd = 3;
		create_heredoc(t);
	}
	while (t->current_cmd < t->argc - 1)
	{
		if (pipe(t->head_child->fd) == -1)
			oops_crash(t, "Error: 'pipe' failed in master process\n");
		t->head_child->pid = fork();
		if (t->head_child->pid == -1)
			oops_crash(t, "Error: 'fork' failed in master process\n");
		else if (t->head_child->pid == 0)
			redir_exec(t);
		t->current_cmd++;
		t->head_child = t->head_child->next_child;
	}
	close_all_fds(t);
	waitpid(-1, NULL, 0);
}
