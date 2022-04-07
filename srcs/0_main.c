/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:27:42 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/12 14:27:42 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	start_parent_process(t_pipex *t)
{
	int		pid;

	if (pipe(t->fd) == -1)
		oops_crash(t, "pipex: error: 'pipe' failed\n");
	t->current_cmd = 2;
	while (t->current_cmd < t->argc - 1)
	{
		pid = fork();
		if (pid == -1)
			oops_crash(t, "pipex: error: 'fork' failed\n");
		else if (pid == 0)
			redir_exec(t);
		t->current_cmd++;
	}
	close(t->fd[IN]);
	close(t->fd[OUT]);
	close(t->infile);
	close(t->outfile);
	while (waitpid(-1, NULL, 0) != -1)
		;
}

static void	open_files(t_pipex *t)
{
	t->infile = open(t->argv[1], O_RDONLY);
	if (t->infile < 0)
		display_file_error(t, t->argv[1]);
	t->outfile = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (t->outfile < 0)
		display_file_error(t, t->argv[t->argc - 1]);
}

static void	init_pipex(t_pipex *t, int argc, char *argv[], char *envp[])
{
	t->argc = argc;
	t->argv = argv;
	t->envp = envp;
	t->nb_cmds = t->argc - 3;
	t->command = NULL;
	t->all_paths = NULL;
	t->exec_path = NULL;
	t->full_line = NULL;
}

static void	launch_pipex(t_pipex *t, int argc, char *argv[], char *envp[])
{
	init_pipex(t, argc, argv, envp);
	open_files(t);
	start_parent_process(t);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex		t[1];

	if (argc != 5)
	{
		ft_putstr_fd("pipex: error: invalid number of arguments\n", 2);
		ft_putstr_fd("Usage: ", 2);
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n", 2);
		return (127);
	}
	else
		launch_pipex(t, argc, argv, envp);
	free_all(t);
	return (0);
}
