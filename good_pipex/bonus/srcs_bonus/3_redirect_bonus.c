/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_redirect_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:58:33 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/31 13:58:33 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	redir_first_command(t_pipex *t)
{
	int		a;
	int		b;

	a = dup2(t->infile, STDIN_FILENO);
	b = dup2(t->fd_pipes[1], STDOUT_FILENO);
	if (a == -1 || b == -1)
		oops_crash(t, "pipex_bonus: error: 'dup2' failed for first command\n");
}

static void	redir_last_command(t_pipex *t)
{
	int		a;
	int		b;

	a = dup2(t->fd_pipes[2 * t->index - 2], STDIN_FILENO);
	b = dup2(t->outfile, STDOUT_FILENO);
	if (a == -1 || b == -1)
		oops_crash(t, "pipex_bonus: error: 'dup2' failed for last command\n");
}

static void	redir_any_command(t_pipex *t)
{
	int		a;
	int		b;

	a = dup2(t->fd_pipes[2 * t->index - 2], STDIN_FILENO);
	b = dup2(t->fd_pipes[2 * t->index + 1], STDOUT_FILENO);
	if (a == -1 || b == -1)
		oops_crash(t, "pipex_bonus: error: 'dup2' failed for middle command\n");
}

void	redir_exec(t_pipex *t)
{	
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		oops_crash(t, "pipex_bonus: error: 'fork' failed in parent process\n");
	else if (pid == 0)
	{
		if (t->index == 0)
			redir_first_command(t);
		else if (t->index == (t->nb_cmds - 1))
			redir_last_command(t);
		else
			redir_any_command(t);
		close_pipes(t);
		execute_command(t);
	}
}
