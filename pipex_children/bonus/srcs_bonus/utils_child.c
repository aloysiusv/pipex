/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:35:01 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/24 21:32:23 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static t_child	*create_child()
{
	t_child	*child;

	child = (t_child *)malloc(sizeof(t_child));
	if (child == NULL)
		return (NULL);
	child->command = NULL;
	child->all_paths = NULL;
	child->full_path = NULL;
	child->prev_child = child;
	child->next_child = child;
	return (child);
}

t_child	*add_next_child(t_child *current_child)
{
	t_child	*next;

	next = create_child();
	if (next == NULL)
		return (NULL);
	if (current_child)
	{
		next->prev_child = current_child;
		next->next_child = current_child->prev_child;
		current_child->next_child = next;
	}
	else
		current_child = next;
	return (next);
}
