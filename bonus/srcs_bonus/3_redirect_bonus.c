/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_redirect_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:56:37 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/21 19:56:37 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	redir_first_command(t_pipex *t)
{
	if (t->heredoc == NO)
		dup2(t->fdin, STDIN_FILENO);
	dup2(t->fd[WRITE], STDOUT_FILENO);
	close(t->fd[WRITE]);
	close(t->fd[READ]);
}

static void	redir_last_command(t_pipex *t)
{
	dup2(t->fdout, STDOUT_FILENO);
	dup2(t->fd[READ], STDIN_FILENO);
	close(t->fd[READ]);
	close(t->fd[WRITE]);
}

static void	redir_any_command(t_pipex *t)
{
	int	tmp_fd[2];
	
	if (pipe(tmp_fd) == -1)
		oops_crash(t, "Error: 'pipe' failed in slave process\n");
	dup2(tmp_fd[READ], STDIN_FILENO);
	dup2(tmp_fd[WRITE], STDOUT_FILENO);
	close(tmp_fd[READ]);
	close(tmp_fd[WRITE]);
	close(t->fd[WRITE]);
	close(t->fd[READ]);
}

void	redir_exec(t_pipex *t)
{	
	if (t->current_cmd == 2 || (t->current_cmd == 3 && t->heredoc == 1))
		redir_first_command(t);
	else if (t->current_cmd == t->argc - 2)
		redir_last_command(t);
	else
		redir_any_command(t);
	execute_command(t);
}
