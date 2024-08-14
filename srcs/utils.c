/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:12:35 by jfita             #+#    #+#             */
/*   Updated: 2024/05/02 14:04:02 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *pipex, char **argv, int argc)
{
	if (!pipex->here_doc)
		pipex->input_file = open(argv[1], O_RDONLY, 0777);
	if (pipex->input_file == -1)
	{
		perror("error opening infiles\n");
		pipex->inv_input = 1;
	}
	if (pipex->here_doc)
		pipex->output_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0777);
	else
		pipex->output_file = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0777);
	if (pipex->output_file == -1)
		perror("error opening outfiles\n");
}

void	open_pipes(t_pipex *pipex)
{
	int	cmd_count;

	cmd_count = pipex->cmd_count;
	pipex->pipes = malloc((cmd_count - 1) * sizeof(int *));
	if (pipex->pipes == NULL)
		error_exit(pipex, "malloc error\n", 1);
	test_pipes(pipex);
}

void	test_pipes(t_pipex *pipex)
{
	int	i;
	int	cmd_count;

	i = 0;
	cmd_count = pipex->cmd_count;
	while (i < cmd_count - 1)
	{
		pipex->pipes[i] = malloc(2 * sizeof(int));
		pipex->nb_pipes++;
		if (pipe(pipex->pipes[i]) == -1)
		{
			free_pipes(pipex);
			error_exit(pipex, "pipe error\n", 1);
		}
		i++;
	}
}

void	cleanup_pipes(t_pipex *pipex)
{
	int	i;

	i = pipex->nb_pipes - 1;
	while (i >= 0)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i--;
	}
}

void	free_pipes(t_pipex *pipex)
{
	int	i;

	i = pipex->nb_pipes - 1;
	while (i >= 0)
	{
		if (pipex->pipes[i])
			free(pipex->pipes[i]);
		pipex->pipes[i] = NULL;
		i--;
	}
	free(pipex->pipes);
}
