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
	dup2(t->infile, STDIN_FILENO);
	dup2(t->pipes[t->cmd_pos], STDOUT_FILENO);
}

static void	redir_last_command(t_pipex *t)
{
	dup2(t->outfile, STDOUT_FILENO);
	dup2(t->pipes[t->cmd_pos], STDIN_FILENO);
}

static void redir_any_command(t_pipex *t)
{
	dup2(t->pipes[t->cmd_pos], STDIN_FILENO);
	dup2(t->pipes[t->cmd_pos + 1], STDOUT_FILENO);
}

void	make_slaves(t_pipex *t, char *argv[])
{
	int		*pid;

	t->cmd_pos = 0;
	while (t->cmd_pos < t->nb_commands)
	{
		pid[t->cmd_pos] = fork();
		if (pid[t->cmd_pos] == 0)
		{
			if (t->cmd_pos == 0)
				redir_first_command(t);
			else if (t->cmd_pos == (t->nb_commands - 1))
				redir_last_command(t);
			else
				redir_any_command(t);
			close_pipes(t);
			execute_command(t, argv);
		}
		else 
		{
			ft_putstr_fd("Error: failed to create a slave process", 2);
			free_all(t);
			exit(EXIT_FAILURE)
		}
		t->cmd_pos++;
	}
}
