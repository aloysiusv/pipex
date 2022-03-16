/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 02:28:36 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/11 02:28:36 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	execute_command(t_pipex *t)
{
	size_t	i;

	t->command = ft_split(t->argv[t->current_cmd], ' ');
	if (t->command == NULL)
		oops_crash(t, "Error: failed to retrieve command\n");
	i = 0;
	get_formatted_paths(t);
	while (t->all_paths_slash[i])
	{
		t->full_path = ft_strjoin(t->all_paths_slash[i], t->command[0]);
		if (t->full_path == NULL)
			oops_crash(t, "Error: full_path join failed\n");
		if (access(t->full_path, F_OK) == 0)
		{
			if (execve(t->full_path, t->command, 0) == -1)
				oops_crash(t, "Error: execve system call failed\n");
		}
		free(t->full_path);
		i++;
	}
	oops_crash(t, "Error: command not found\n");
}