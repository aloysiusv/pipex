/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_a_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:57:48 by lrandria          #+#    #+#             */
/*   Updated: 2022/04/06 15:57:48 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static void	create_path(t_pipex *t)
{
	size_t	i;

	i = 0;
	while (t->full_line[i])
	{
		if (t->full_line[i] == ' ')
			break ;
		i++;
	}
	t->exec_path = ft_substr(t->full_line, 0, i);
	if (t->exec_path == NULL)
		oops_crash(t, "pipex: error: 'malloc' failed\n");
}

static void	create_command(t_pipex *t)
{
	size_t	i;
	char	*tmp_cmd;

	i = ft_strlen(t->full_line) - 1;
	while (t->full_line[i])
	{
		if (t->full_line[i] == '/')
			break ;
		i--;
	}
	tmp_cmd = ft_substr(t->full_line, i + 1, ft_strlen(t->full_line));
	if (tmp_cmd == NULL)
		oops_crash(t, "pipex: error: 'malloc' failed\n");
	t->command = ft_split(tmp_cmd, ' ');
	if (t->command == NULL)
	{
		free(tmp_cmd);
		oops_crash(t, "pipex: error: 'malloc' failed\n");
	}
	free(tmp_cmd);
}

static void	execute_full_path_cmd(t_pipex *t)
{
	create_path(t);
	create_command(t);
	if (access(t->exec_path, F_OK | X_OK) == FOUND)
	{
		if (execve(t->exec_path, t->command, t->envp) == -1)
			oops_crash(t, "pipex: error: execve system call failed\n");
	}
	display_cmd_error(t, t->full_line);
}

void	execute_command(t_pipex *t)
{
	size_t	last_char;

	t->full_line = t->argv[t->current_cmd];
	last_char = ft_strlen(t->full_line) - 1;
	if (t->full_line[0] == ' ' || t->full_line[last_char] == ' ')
		display_cmd_error(t, t->full_line);
	if (find_char(t->full_line, '/') == FOUND)
		execute_full_path_cmd(t);
	else
		execute_env_var_command(t);
	display_cmd_error(t, t->full_line);
}
