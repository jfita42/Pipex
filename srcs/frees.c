/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:00:47 by jfita             #+#    #+#             */
/*   Updated: 2024/05/02 14:01:38 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *pipex)
{
	if (pipex->envp_paths != NULL)
		free_paths(pipex);
	if (pipex->cmd_args)
	{
		free_cmd_args(pipex);
	}
	if (pipex->exec != NULL)
		free_exec(pipex);
	free(pipex);
	pipex = NULL;
}

void	free_cmd_args(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	while (pipex->cmd_args[i])
	{
		j = 0;
		while (pipex->cmd_args[i][j])
		{
			free(pipex->cmd_args[i][j]);
			j++;
		}
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	pipex->cmd_args = NULL;
}

void	free_exec(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex->exec)
	{
		while (i < pipex->cmd_count)
		{
			free(pipex->exec[i]);
			i++;
		}
		free(pipex->exec);
		pipex->exec = NULL;
	}
}

void	free_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->envp_paths[i])
	{
		free(pipex->envp_paths[i]);
		i++;
	}
	free(pipex->envp_paths);
	pipex->envp_paths = NULL;
}
