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

void	redir_exec(t_pipex *t)
{	
	if (t->current_cmd == 2)
		redir_first_command(t);
	else if (t->current_cmd == t->argc - 2)
		redir_last_command(t);
	execute_command(t);
}
