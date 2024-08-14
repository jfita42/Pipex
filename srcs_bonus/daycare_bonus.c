/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   daycare_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:54:40 by jfita             #+#    #+#             */
/*   Updated: 2024/05/02 14:06:50 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		first_child(pipex);
	}
	if (i > 0)
	{
		mid_child(pipex, i);
	}
	if (i < pipex->cmd_count - 1)
	{
		all_but_last_child(pipex, i);
	}
	if (i == pipex->cmd_count - 1)
	{
		last_child(pipex);
	}
	exec(pipex, i);
}

void	first_child(t_pipex *pipex)
{
	if (dup2(pipex->input_file, STDIN_FILENO) == -1)
	{
		cleanup_pipes(pipex);
		if (pipex->output_file >= 0)
			close(pipex->output_file);
		free_pipes(pipex);
		error_exit(pipex, "Error exec\n", 1);
	}
	close(pipex->input_file);
	close(pipex->output_file);
}

void	mid_child(t_pipex *pipex, int i)
{
	dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
	dup2(pipex->pipes[i - 1][1], STDOUT_FILENO);
	close(pipex->pipes[i - 1][0]);
	close(pipex->pipes[i - 1][1]);
}

void	all_but_last_child(t_pipex *pipex, int i)
{
	dup2(pipex->pipes[i][1], STDOUT_FILENO);
	cleanup_pipes(pipex);
	if (pipex->input_file >= 0)
		close(pipex->input_file);
	if (pipex->output_file >= 0)
		close(pipex->output_file);
}

void	last_child(t_pipex *pipex)
{
	int	i;

	if (dup2(pipex->output_file, STDOUT_FILENO) == -1)
	{
		cleanup_pipes(pipex);
		free_pipes(pipex);
		error_exit(pipex, NULL, 1);
	}
	if (pipex->output_file >= 0)
		close(pipex->output_file);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}
