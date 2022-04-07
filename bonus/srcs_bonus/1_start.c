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

void	start_parent_process(t_pipex *t)
{
	t->index = 0;
	t->current_cmd = 2;
	if (t->heredoc == YES)
	{
		t->current_cmd = 3;
		t->nb_cmds = t->argc - 4;
		create_heredoc(t);
	}
	open_pipes(t);
	while (t->index < t->nb_cmds)
	{
		redir_exec(t);
		t->index++;
		t->current_cmd++;
	}
	close_pipes(t);
	close(t->infile);
	close(t->outfile);
	while (waitpid(-1, NULL, 0) != -1)
		;
	if (t->heredoc == YES)
		unlink("tmp_heredoc");
}
