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

// void	special_wait(t_pipex *t)
// {
// 	int	status;

// 	if (ft_strncmp(t->argv[1], "/dev/stdin", 10) == FOUND
// 		|| ft_strncmp(t->argv[1], "/dev/fd/0", 9) == FOUND)
// 	{
// 		ft_putstr_fd("pipex: warning: this is not minishell\n", 2);
// 		while (waitpid(-1, &status, 0) != -1)
// 			;
// 	}
// 	else
// 		waitpid(-1, &status, 0);
// }

void	start_parent_process(t_pipex *t)
{
	int		pid;
	int		status;

	if (pipe(t->fd) == -1)
		oops_crash(t, "pipex: error: 'pipe' failed in parent process\n");
	t->current_cmd = 2;
	if (t->heredoc == YES)
	{
		t->current_cmd = 3;
		t->nb_cmds = t->argc - 4;
		create_heredoc(t);
	}
	while (t->current_cmd < t->argc - 1)
	{
		pid = fork();
		if (pid == -1)
			oops_crash(t, "pipex: error: 'fork' failed in parent process\n");
		else if (pid == 0)
			redir_exec(t);
		t->current_cmd++;
	}
	close(t->fd[IN]);
	close(t->fd[OUT]);
	waitpid(-1, &status, 0);
	// special_wait(t);
}
