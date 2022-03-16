/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_find_all_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 01:33:13 by lrandria          #+#    #+#             */
/*   Updated: 2022/03/15 01:33:13 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	extract_path(t_pipex *t)
{
	size_t	i;

	if (!t->envp && !t->command)
		return (0);
	i = 0;
	while (ft_strncmp(t->envp[i], "PATH=", 5) != 0)
		i++;
	t->all_paths = ft_split(t->envp[i] + 5, ':');
	i = 0;
	while (t->all_paths[i])
	{
		t->path_slash = ft_strjoin(t->all_paths[i], "/");
		t->full_path = ft_strjoin(t->path_slash, t->command);
		free(t->path_slash);
		if (access(t->full_path, F_OK) == 0)
			return (t->full_path);
		free(t->full_path);
		i++;
	}
	free_strings(t->all_paths);
}

void	get_path(t_pipex *t)
{
	char	*command;
	char	*full_command;

	command = ft_split(t->argv[t->current_cmd], ' ');

}