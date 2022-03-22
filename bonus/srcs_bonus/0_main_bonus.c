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
	if (ft_strncmp(t->argv[1], "here_doc", 8) == FOUND)
	{
		t->heredoc = 1;
		t->limiter = t->argv[2];
		t->fdout = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_APPEND,
				0644);
	}
	else
	{
		t->fdin = open(t->argv[1], O_RDONLY);
		if (t->fdin < 0)
			oops_crash(t, "Error: can't open infile\n");
		t->fdout = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	}
	if (t->fdout < 0)
		oops_crash(t, "Error: can't open/create outfile\n");
}

static void	init_pipex(t_pipex *t, int argc, char *argv[], char *envp[])
{
	t->argc = argc;
	t->argv = argv;
	t->envp = envp;
	t->nb_cmds = t->argc - 3;
	t->command = NULL;
	t->all_paths = NULL;
	t->full_path = NULL;
	t->heredoc = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex		t[1];

	if (argc < 5)
	{
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
		ft_putstr_fd("Usage[1]: ", 2);
		ft_putstr_fd("./pipex infile cmd1...cmd-nth outfile\n", 2);
		ft_putstr_fd("Usage[2]: ", 2);
		ft_putstr_fd("./pipex here_doc limiter cmd1...cmd-nth outfile\n", 2);
		return (1);
	}
	else
	{
		init_pipex(t, argc, argv, envp);
		open_files(t);
		start_master_process(t);
	}
	return (0);
}
