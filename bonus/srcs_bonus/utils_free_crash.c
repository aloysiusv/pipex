/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_crash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 02:34:45 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/15 02:34:45 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

void	free_strings(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	if (tab[i])
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void	free_all(t_pipex *t)
{
	if (t->exec_path)
		free(t->exec_path);
	free_strings(t->all_paths);
	free_strings(t->command);
	if (t->fd_pipes)
	{
		close_pipes(t);
		free(t->fd_pipes);
	}
	if (t->infile_opened == FOUND)
		close(t->infile);
	if (t->outfile_opened == FOUND)
		close(t->outfile);
	if (t->heredoc == FOUND)
		close(t->fd_heredoc);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	oops_crash(t_pipex *t, char *error_message)
{
	ft_putstr_fd(error_message, 2);
	free_all(t);
	exit(127);
}

void	display_cmd_error(t_pipex *t, char *command)
{
	ft_putstr_fd("pipex_bonus: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": ", 2);
	oops_crash(t, "command not found\n");
}

void	display_file_error(t_pipex *t, char *file)
{
	open_pipes(t);
	ft_putstr_fd("pipex_bonus: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	oops_crash(t, "No such file or directory\n");
}
