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

int		execute_command(t_pipex *t, char *argv[])
{
	size_t	i;

	t->command = ft_split(argv[t->cmd_pos], ' ');
	t->bin_path[0] = ft_strjoin("/bin/", t->command[0]);
	t->bin_path[1] = ft_strjoin("/usr/bin/", t->command[0]);
	t->bin_path[2] = ft_strjoin("/usr/local/bin/", t->command[0]);
	t->bin_path[3] = ft_strjoin("/usr/sbin/", t->command[0]);
	t->bin_path[4] = ft_strjoin("/sbin/", t->command[0]);
	i = 0;
	while (i < 5)
	{
		execve(t->bin_path[i], t->command, 0);
		i++;
	}
	ft_putstr_fd("Error: command not found\n", 2);
	return (-1);
}
