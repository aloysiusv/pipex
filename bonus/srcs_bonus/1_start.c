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

void	start_master_process(t_pipex *t)
{
	int		pid;
	int		status;

	if (pipe(t->fd) == -1)
		oops_crash(t, "Error: 'pipe' failed in master process\n");
	t->current_cmd = 2;
	if (t->heredoc == YES)
	{
		t->current_cmd = 3;
		create_heredoc(t);
	}
	while (t->current_cmd < t->argc - 1)
	{
		pid = fork();
		if (pid == -1)
			oops_crash(t, "Error: 'fork' failed in master process\n");
		else if (pid == 0)
			redir_exec(t);
		t->current_cmd++;
	}
	close(t->fd[READ]);
	close(t->fd[WRITE]);
	while (waitpid(-1, &status, 0) != -1)
		;
}
