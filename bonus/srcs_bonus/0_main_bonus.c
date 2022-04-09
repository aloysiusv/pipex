/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 08:04:25 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/22 08:04:25 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	open_files(t_pipex *t)
{
	if (t->heredoc == FOUND)
		t->outfile = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_APPEND,
				0644);
	else
	{
		t->infile = open(t->argv[1], O_RDONLY);
		if (t->infile < 0)
			display_file_error(t, t->argv[1]);
		t->infile_opened = FOUND;
		t->outfile = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	}
	if (t->outfile < 0)
		display_file_error(t, t->argv[t->argc - 1]);
	t->outfile_opened = FOUND;
}

static void	get_info_heredoc(t_pipex *t)
{
	if (t->argc < 6)
	{
		ft_putstr_fd("pipex_bonus: error: invalid number of arguments\n", 2);
		ft_putstr_fd("Usage[2]: ", 2);
		oops_crash(t, "./pipex_bonus here_doc delim cmd1...cmdN outfile\n");
	}
	t->heredoc = FOUND;
	t->limiter = t->argv[2];
	t->current_cmd = 3;
	t->nb_cmds = t->argc - 4;
}

static void	init_infos(t_pipex *t, int argc, char *argv[], char *envp[])
{
	t->argc = argc;
	t->argv = argv;
	t->envp = envp;
	t->nb_cmds = t->argc - 3;
	t->current_cmd = 2;
	t->command = NULL;
	t->all_paths = NULL;
	t->exec_path = NULL;
	t->full_line = NULL;
	t->index = 0;
	t->fd_pipes = 0;
	t->infile = 0;
	t->outfile = 0;
	t->infile_opened = NOT_FOUND;
	t->outfile_opened = NOT_FOUND;
	t->heredoc = NOT_FOUND;
	if (ft_strncmp(t->argv[1], "here_doc", 9) == FOUND)
		get_info_heredoc(t);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex		t[1];

	if (argc < 5)
	{
		ft_putstr_fd("pipex_bonus: error: invalid number of arguments\n", 2);
		ft_putstr_fd("Usage[1]: ", 2);
		ft_putstr_fd("./pipex_bonus infile cmd1...cmdN outfile\n", 2);
		ft_putstr_fd("Usage[2]: ", 2);
		ft_putstr_fd("./pipex_bonus here_doc limiter cmd1...cmdN outfile\n", 2);
		return (127);
	}
	else
	{
		init_infos(t, argc, argv, envp);
		open_files(t);
		start_parent_process(t);
	}
	free_all(t);
	return (0);
}
