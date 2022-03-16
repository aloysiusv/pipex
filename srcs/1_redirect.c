/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_redirect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:04:28 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/13 17:04:28 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	redir_first_command(t_pipex *t)
{
	dup2(t->fdin, STDIN_FILENO);
	close(t->fd[READ]);
	dup2(t->fd[WRITE], STDOUT_FILENO);
	close(t->fd[WRITE]);
}

static void	redir_last_command(t_pipex *t)
{
	dup2(t->fdout, STDOUT_FILENO);
	close(t->fd[WRITE]);
	dup2(t->fd[READ], STDIN_FILENO);
	close(t->fd[READ]);
}

static void redir_any_command(t_pipex *t)
{
	dup2(t->fd[READ], STDIN_FILENO);
	dup2(t->fd[WRITE], STDOUT_FILENO);
	close(t->fd[READ]);
	close(t->fd[WRITE]);
}

void	redir_exec(t_pipex *t)
{	
	if (t->current_cmd == 2)
		redir_first_command(t);
	else if (t->current_cmd == t->argc - 1)
		redir_last_command(t);
	else
		redir_any_command(t);
	execute_command(t);
}
