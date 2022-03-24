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
		t->outfile = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_APPEND,
				0644);
	}
	else
	{
		t->infile = open(t->argv[1], O_RDONLY);
		if (t->infile < 0)
			oops_crash(t, "Error: can't open infile\n");
		t->outfile = open(t->argv[t->argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
				0644);
	}
	if (t->outfile < 0)
		oops_crash(t, "Error: can't open/create outfile\n");
}

static void	init_pipex(t_pipex *t, int argc, char *argv[], char *envp[])
{
	t_child	*new;
	size_t	i;
	
	t->argc = argc;
	t->argv = argv;
	t->envp = envp;
	t->heredoc = 0;
	t->nb_cmds = t->argc - 3;
	t->head_child = (t_child *)malloc(sizeof(t_child));
	if (t->head_child == NULL)
		oops_crash(t, "Error: couldn't malloc 'head_child'\n");
	while (i < t->nb_cmds)
	{
		new = add_next_child(t->head_child);
		if (new == NULL)
			oops_crash(t, "Error: couldn't malloc 'next_child'\n");
		t->head_child = t->head_child->next_child;
		i++;
	}
	t->head_child = t->head_child->next_child;
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
		delete_children(t);
	}
	return (0);
}
