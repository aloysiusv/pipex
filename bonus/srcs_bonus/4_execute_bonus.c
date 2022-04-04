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

static void	display_cmd_error(t_pipex *t, char *str)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	oops_crash(t, "command not found\n");
}

static void	get_paths_get_command(t_pipex *t)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (t->envp[i] == NULL)
		oops_crash(t, "pipex: error: environment variables not found\n");
	while (t->envp[i])
	{
		if (ft_strncmp(t->envp[i], "PATH=", 5) == FOUND)
		{
			tmp = ft_substr(t->envp[i], 5, ft_strlen(t->envp[i]));
			if (tmp == NULL)
				display_cmd_error(t, t->argv[t->current_cmd]);
			t->all_paths = ft_split(tmp, ':');
			if (t->all_paths == NULL)
				display_cmd_error(t, t->argv[t->current_cmd]);
			free(tmp);
		}
		i++;
	}
	if (t->all_paths == NULL)
		display_cmd_error(t, t->argv[t->current_cmd]);
	t->command = ft_split(t->argv[t->current_cmd], ' ');
	if (t->command == NULL)
		display_cmd_error(t, t->argv[t->current_cmd]);
}

static void	add_slash_to_path(t_pipex *t, size_t i)
{
	char	*tmp;

	tmp = ft_strjoin(t->all_paths[i], "/");
	if (t->all_paths[i][ft_strlen(t->all_paths[i]) - 1] != '/')
		t->full_path = ft_strjoin(tmp, t->command[0]);
	else
		t->full_path = ft_strjoin(t->all_paths[i], t->command[0]);
	if (t->full_path == NULL)
	{
		free(tmp);
		display_cmd_error(t, t->argv[t->current_cmd]);
	}
	free(tmp);
}

void	execute_command(t_pipex *t)
{
	size_t	i;

	i = 0;
	get_paths_get_command(t);
	while (t->all_paths[i])
	{
		add_slash_to_path(t, i);
		if (access(t->full_path, X_OK) == FOUND)
		{
			if (execve(t->full_path, t->command, 0) == -1)
				oops_crash(t, "pipex: error: execve system call failed\n");
		}
		free(t->full_path);
		t->full_path = NULL;
		i++;
	}
	oops_crash(t, "pipex: error: permission denied\n");
}
