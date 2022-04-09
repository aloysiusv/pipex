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
	if (t->heredoc == FOUND)
		create_heredoc(t);
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
	if (t->heredoc == FOUND)
		unlink("tmp_heredoc");
}
