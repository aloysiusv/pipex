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

static void	start_master_process(t_pipex *t)
{
	int		pid;
	int		status;

	if (pipe(t->fd) == -1)
		oops_crash(t, "Error: 'pipe' failed\n");
	t->current_cmd = 2;
	while (t->current_cmd < t->argc - 1)
	{
		pid = fork();
		if (pid == -1)
			oops_crash(t, "Error: failed to create new process\n");
		else if (pid == 0)
			redir_exec(t);
		t->current_cmd++;
	}
	close(t->fd[READ]);
	close(t->fd[WRITE]);
	while (waitpid(-1, &status, 0) != -1)
		;
}

static void	open_files(t_pipex *t)
{
	t->fdin = open(t->argv[1], O_RDONLY);
	if (t->fdin < 0)
		oops_crash(t, "Error: can't open infile\n");
	t->fdout = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
}

static void	launch_pipex(t_pipex *t, int argc, char *argv[], char *envp[])
{
	init_pipex(t, argc, argv, envp);
	open_files(t);
	start_master_process(t);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex		t[1];

	if (argc != 5)
		ft_putstr_fd("Error: invalid number of arguments\n", 2);
	else
		launch_pipex(t, argc, argv, envp);
	return (0);
}
