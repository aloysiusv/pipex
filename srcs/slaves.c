/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slaves.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 02:13:21 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/11 02:13:21 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	redir_first_command(t_pipex *t)
{
	dup2(t->infile, 0);
	dup2(t->pipes[1], 1);
}

static void	redir_last_command(t_pipex *t)
{
	dup2(t->pipes[2 * t->cmd_pos - 2], 0);
	dup2(t->outfile, 1);
}

void	make_slaves(t_pipex *t, char *argv[])
{
	int		pid;

	while (t->cmd_pos < t->nb_commands)
	{
		pid = fork();
		if (pid == 0)
		{
			if (t->cmd_pos == 0)
				redir_first_command(t);
			else if (t->cmd_pos == (t->nb_commands - 1))
				redir_last_command(t);
			else
			{
				dup2(t->pipes[2 * t->cmd_pos - 2], 0);
				dup2(t->pipes[2 * t->cmd_pos + 1], 1);
			}
		}
		t->cmd_pos++;
	}
	close_pipes(t);
	execute_command(t, argv);
}
