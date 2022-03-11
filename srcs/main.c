/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 01:08:35 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/11 01:08:35 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void launch_master_process(t_pipex *t, char *argv[])
{
	size_t	i;

	i = 0;
	open_pipes(t);
	make_slaves(t, argv);
	close_pipes(t);
	while (i < t->nb_commands)
	{
		wait(NULL);
		i++;
	}
}

static void	open_files(t_pipex *t, int argc, char *argv[])
{
	t->infile = open(argv[1], O_RDONLY);
	t->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (t->infile < 0 || t->outfile < 0)
	{
		ft_putstr_fd("Error: can't open files\n", 2);
		exit(EXIT_FAILURE);
	}
}

static void	init_pipex(t_pipex *t, int argc, char *argv[])
{
	t = (t_pipex*)malloc(sizeof(t_pipex));
	if (t == NULL)
		exit(EXIT_FAILURE);
	t->nb_commands = argc - 3;
	t->nb_pipes = t->nb_commands - 1;
	open_files(t, argc, argv);
}

int	main(int argc, char *argv[])
{
	t_pipex		t[1];

	if (argc == 5)
	{
		init_pipex(t, argc, argv);
		launch_master_process(t, argv);
	}
	else
		ft_putstr_fd("Error: not enough arguments\n", 2);
	free_all(t);
	return (0);
}
