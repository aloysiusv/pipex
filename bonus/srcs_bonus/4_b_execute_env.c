/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_b_execute_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:05:59 by lrandria          #+#    #+#             */
/*   Updated: 2022/04/09 18:05:59 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	create_env_paths(t_pipex *t)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (t->envp[i])
	{
		if (ft_strncmp(t->envp[i], "PATH=", 5) == FOUND)
		{
			tmp = ft_substr(t->envp[i], 5, ft_strlen(t->envp[i]));
			if (tmp == NULL)
				oops_crash(t, "pipex: error: 'malloc' failed\n");
			t->all_paths = ft_split(tmp, ':');
			if (t->all_paths == NULL)
			{
				free(tmp);
				oops_crash(t, "pipex: error:  'malloc' failed\n");
			}
			free(tmp);
		}
		i++;
	}
	if (t->all_paths == NULL)
		display_cmd_error(t, t->argv[t->current_cmd]);
}

static void	add_slash_to_path(t_pipex *t, size_t i)
{
	char	*tmp;

	tmp = ft_strjoin(t->all_paths[i], "/");
	if (t->all_paths[i][ft_strlen(t->all_paths[i]) - 1] != '/')
		t->exec_path = ft_strjoin(tmp, t->command[0]);
	else
		t->exec_path = ft_strjoin(t->all_paths[i], t->command[0]);
	if (t->exec_path == NULL)
	{
		free(tmp);
		oops_crash(t, "pipex: error: 'malloc' failed\n");
	}
	free(tmp);
}

void	execute_env_var_command(t_pipex *t)
{
	size_t	i;

	create_env_paths(t);
	i = 0;
	while (t->all_paths[i])
	{
		add_slash_to_path(t, i);
		if (access(t->exec_path, F_OK | X_OK) == 0)
		{
			if (execve(t->exec_path, t->command, t->envp) == -1)
				oops_crash(t, "pipex: error: execve system call failed\n");
		}
		free(t->exec_path);
		t->exec_path = NULL;
		i++;
	}
}
