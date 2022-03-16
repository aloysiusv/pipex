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

void	start_master_process(t_pipex *t)
{
	int		pid;
	int		status;
	size_t	i;

	i = 0;
	t->current_cmd = 2;
	while (t->current_cmd < t->argc - 1)
	{
		pipe(t->pipes);
		pid = fork();
		if (pid == -1)
			oops_crash(t, "Error: failed to create new process\n");
		else if (pid == 0)
			redir_exec(t);
		t->current_cmd++;
		i++;
	}
	waitpid(-1, &status, 0);
}

static void	launch_pipex(t_pipex *t, int argc, char *argv[], char *envp[])
{
	t->argc = argc;
	t->argv = argv;
	t->envp = envp;
	t->nb_cmds = t->argc - 3;
	t->fdin = open(t->argv[1], O_RDONLY);
	t->fdout = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (t->fdin < 0 || t->fdout < 0)
		oops_crash(t, "Error: can't open files\n");
	start_master_process(t);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex		t[1];

	if (argc < 5)
		ft_putstr_fd("Error: not enough arguments\n", 2);
	else
		launch_pipex(t, argc, argv, envp);
	return (0);
}
