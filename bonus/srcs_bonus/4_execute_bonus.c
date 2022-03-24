/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:42:53 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/17 17:42:53 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	get_paths_get_command(t_pipex *t)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (t->envp[i] == NULL)
		oops_crash(t, "Error: environment variables not found\n");
	while (t->envp[i])
	{
		if (ft_strncmp(t->envp[i], "PATH=", 5) == FOUND)
		{
			tmp = ft_substr(t->envp[i], 5, ft_strlen(t->envp[i]));
			if (tmp == NULL)
				oops_crash(t, "Error: failed to extract $PATH\n");
			t->head_child->all_paths = ft_split(tmp, ':');
			if (t->head_child->all_paths == NULL)
				oops_crash(t, "Error: failed to retrieve all paths\n");
			free(tmp);
		}
		i++;
	}
	if (t->head_child->all_paths == NULL)
		oops_crash(t, "Error: failed to retrieve all paths\n");
	t->head_child->command = ft_split(t->argv[t->current_cmd], ' ');
	if (t->head_child->command == NULL)
		oops_crash(t, "Error: failed to extract command\n");
}

static void	add_slash_to_path(t_pipex *t, size_t i)
{
	char	*tmp;

	tmp = ft_strjoin(t->head_child->all_paths[i], "/");
	if (t->head_child->all_paths[i][ft_strlen(t->head_child->all_paths[i]) - 1] != '/')
		t->head_child->full_path = ft_strjoin(tmp, t->head_child->command[0]);
	else
		t->head_child->full_path = ft_strjoin(t->head_child->all_paths[i], t->head_child->command[0]);
	if (t->head_child->full_path == NULL)
	{
		free(tmp);
		oops_crash(t, "Error: can't get full path\n");
	}
	free(tmp);
}

void	execute_command(t_pipex *t)
{
	size_t	i;

	i = 0;
	get_paths_get_command(t);
	while (t->head_child->all_paths[i])
	{
		add_slash_to_path(t, i);
		if (access(t->head_child->full_path, F_OK) == 0)
		{
			if (execve(t->head_child->full_path, t->head_child->command, 0) == -1)
				oops_crash(t, "Error: execve system call failed\n");
		}
		free(t->head_child->full_path);
		t->head_child->full_path = NULL;
		i++;
	}
	oops_crash(t, "Error: command not found\n");
}
