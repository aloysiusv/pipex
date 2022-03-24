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
	dup2(t->head_child->fd[OUT], STDOUT_FILENO);
	close(t->head_child->fd[OUT]);
	close(t->head_child->fd[IN]);
}

static void	redir_last_command(t_pipex *t)
{
	dup2(t->outfile, STDOUT_FILENO);
	dup2(t->head_child->fd[IN], STDIN_FILENO);
	close(t->head_child->fd[IN]);
	close(t->head_child->fd[OUT]);
}

static void	redir_any_command(t_pipex *t)
{
	dup2(t->head_child->fd[IN], STDIN_FILENO);
	dup2(t->head_child->fd[OUT], STDOUT_FILENO);
	close(t->head_child->fd[IN]);
	close(t->head_child->fd[OUT]);
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
