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

#include "../inc/pipex.h"

static void	free_strings(char **tab)
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
	tab = NULL;
}

void	free_all(t_pipex *t)
{
	if (t->full_path)
		free(t->full_path);
	if (t->all_paths)
		free_strings(t->all_paths);
	if (t->command)
		free_strings(t->command);
	if (t->infile)
		close(t->infile);
	if (t->outfile)
		close(t->outfile);
}

void	oops_crash(t_pipex *t, char *error_message)
{
	free_all(t);
	ft_putstr_fd(error_message, 2);
	exit(127);
}
