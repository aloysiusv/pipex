/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_a_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:05:48 by lrandria          #+#    #+#             */
/*   Updated: 2022/04/09 18:05:48 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/pipex_bonus.h"

static void	check_extra_spaces(t_pipex *t)
{
	size_t	last_char;

	t->full_line = t->argv[t->current_cmd];
	last_char = ft_strlen(t->full_line) - 1;
	if (t->full_line[0] == ' ' || t->full_line[last_char] == ' ')
		display_cmd_error(t, t->full_line);
}

static void	execute_full_path_cmd(t_pipex *t)
{
	if (access(t->command[0], F_OK | X_OK) == FOUND)
	{
		if (execve(t->command[0], t->command, t->envp) == -1)
			oops_crash(t, "pipex: error: execve system call failed\n");
	}
	display_cmd_error(t, t->full_line);
}

void	execute_command(t_pipex *t)
{
	check_extra_spaces(t);
	t->command = ft_split(t->argv[t->current_cmd], ' ');
	if (t->command == NULL)
		oops_crash(t, "pipex: error: 'malloc' failed\n");
	if (find_char(t->command[0], '/') == FOUND)
		execute_full_path_cmd(t);
	else
		execute_env_var_command(t);
	display_cmd_error(t, t->full_line);
}
