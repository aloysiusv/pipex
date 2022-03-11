/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 02:51:42 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/11 02:51:42 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	create_pipes(t_pipex *t)
{
	size_t	i;

	t->pipes = (int*)malloc(sizeof(int) * (t->nb_commands - 1));
	if (t->pipes == NULL)
	{
		ft_putstr_fd("Error: couldn't malloc pipe array\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < (t->nb_commands - 1))
	{
		if (pipe(&t->pipes[2 * i]) < 0)
		{
			ft_putstr_fd("Error: couldn't create pipes\n", 2);
			free(t->pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_pipes(t_pipex *t)
{
	size_t	i;

	i = 0;
	while (i < t->nb_commands)
	{
		close(t->pipes[i]);
		i++;
	}
}