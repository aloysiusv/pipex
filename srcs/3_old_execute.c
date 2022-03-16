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
	const char *paths[] = {
		"/usr/local/bin/",
		"/usr/local/sbin/",
		"/usr/bin/",
		"/usr/sbin/",
		"/bin/",
		"/sbin/"
	};
	size_t	i;

	t->command = ft_split(t->argv[t->current_cmd], ' ');
	if (t->command == NULL)
		oops_crash(t, "Error: ft_split failed to malloc\n");
	i = 0;
	// ft_putstr_fd("Command is ", 2); 
	// ft_putstr_fd(t->command[0], 2);
	// ft_putstr_fd("\n", 2);
	while (i < 6)
	{
		t->pathname = ft_strjoin(paths[i], t->command[0]);
		if (t->pathname == NULL)
			oops_crash(t, "Error: pathname join failed\n");
		// ft_putstr_fd("Pathname is ", 2);
		// ft_putstr_fd(t->pathname, 2);
		// ft_putstr_fd("\n", 2);
		if (access(t->pathname, F_OK) == 0)
		{
			// ft_putstr_fd("Will try to execute ", 2);
			// ft_putstr_fd(t->command[0], 2);
			// ft_putstr_fd("\n", 2);
			if (execve(t->pathname, t->command, 0) == -1)
				oops_crash(t, "Error: execve system call failed\n");
		}
		free(t->pathname);
		i++;
	}
	oops_crash(t, "Error: command not found\n");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	t[1];
	(void)argc;
	(void)argv;
	size_t	i;

	isolate_paths(t, envp);
	i = 0;
	while (t->all_paths[i])
	{
		printf("%s\n", t->all_paths[i]);
		i++;
	}
	printf("%s\n", t->no_env_path);
	free(t->no_env_path);
	printf("No env path freed\n");
	free_words(t->all_paths);
	printf("All paths freed\n");
	return (0);
}