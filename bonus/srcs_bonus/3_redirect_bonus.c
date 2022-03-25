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
		dup2(t->infile, STDIN_FILENO);
	dup2(t->fd[OUT], STDOUT_FILENO);
	close(t->fd[OUT]);
	close(t->fd[IN]);
}

static void	redir_last_command(t_pipex *t)
{
	dup2(t->outfile, STDOUT_FILENO);
	dup2(t->fd[IN], STDIN_FILENO);
	close(t->fd[IN]);
	close(t->fd[OUT]);
}

static void	redir_any_command(t_pipex *t)
{
	int	tmp_fd[2];

	if (pipe(tmp_fd) == -1)
		oops_crash(t, "Error: 'pipe' failed in slave process\n");
	dup2(tmp_fd[IN], STDIN_FILENO);
	dup2(tmp_fd[OUT], STDOUT_FILENO);
	close(tmp_fd[IN]);
	close(tmp_fd[OUT]);
	close(t->fd[OUT]);
	close(t->fd[IN]);
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
