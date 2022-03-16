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

static void	extract_path_variable(t_pipex *t)
{
	size_t	i;

	i = 0;
	if (t->envp[i] == NULL)
		oops_crash(t, "Error: environment variables not found\n");
	while (t->envp[i])
	{
		if (ft_strncmp(t->envp[i], "PATH=", 5) == FOUND)
		{
			t->path_variable = ft_substr(t->envp[i], 5, ft_strlen(t->envp[i]));
			if (t->path_variable == NULL)
				oops_crash(t, "Error: failed to extract $PATH\n");
			return ;
		}
		i++;
	}
	oops_crash(t, "Error: $PATH not found\n");
}

static void	add_slash_to_paths(t_pipex *t)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while(t->all_paths[i])
	{
		if (t->all_paths[i][ft_strlen(t->all_paths[i]) - 1] != '/')
		{
			ft_putstr_fd(t->all_paths[i], 2);
			ft_putstr_fd("\n", 2);
			t->all_paths_slash[j] = ft_strjoin(t->all_paths[i], "/");
		}
		j++;
		i++;
	}
}

void	get_formatted_paths(t_pipex *t)
{
	extract_path_variable(t);
	t->all_paths = ft_split(t->path_variable, ':');
	add_slash_to_paths(t);
}
