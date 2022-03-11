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

void	open_files(t_pipex *t, int argc, char *argv[])
{
	t->infile = open(argv[1], O_RDONLY);
	t->outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (t->infile < 0 || t->outfile < 0)
	{
		ft_putstr_fd("Error: can't open files\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	init_pipex(t_pipex *t, int argc, char *argv[])
{
	open_files(t, argc, argv);
	t->nb_commands = argc - 3;
	t->cmd_pos = 0;
}

int	main(int argc, char *argv[])
{
	t_pipex		*t;

	if (argc == 5)
	{
		t = (t_pipex*)malloc(sizeof(t_pipex));
		if (t == NULL)
			return (1);
		init_pipex(t, argc, argv);
		create_pipes(t);
		make_slaves(t, argv);
		close_pipes(t);
		while (wait(NULL) != -1)
			;
	}
	else
		ft_putstr_fd("Error: not enough arguments\n", 2);
	free_all(t);
	return (0);
}
