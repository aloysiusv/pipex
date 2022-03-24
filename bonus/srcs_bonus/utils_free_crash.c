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

#include "../inc_bonus/pipex_bonus.h"

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

static void    delete_child(t_child *child)
{
    if (child == NULL)
		return ;
	if (child->full_path)
		free(child->full_path);
	if (child->all_paths)
		free_strings(child->all_paths);
	if (child->command)
		free_strings(child->command);
	ft_putstr_fd("A child has been deleted\n", 2);
	free(child);
}

void	delete_children(t_pipex *t)
{
	t_child	*tmp;

	if (t->head_child)
	{
		while (t->nb_cmds)
		{
			tmp = t->head_child;
			t->head_child = t->head_child->next_child;
			delete_child(tmp);
			t->nb_cmds--;
		}
		t->head_child = NULL;
	}
}

void	oops_crash(t_pipex *t, char *error_message)
{
	delete_children(t);
	ft_putstr_fd(error_message, 2);
	exit(127);
}
