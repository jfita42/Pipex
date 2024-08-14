/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:10:19 by jfita             #+#    #+#             */
/*   Updated: 2024/05/03 14:42:08 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(t_pipex *pipex, int i)
{
	if (pipex->exec[i])
	{
		if (access(pipex->exec[i], F_OK | X_OK) == -1)
		{
			ft_putendl_fd("No such file or directory", 2);
			cleanup_pipes(pipex);
			free_pipes(pipex);
			error_exit(pipex, "Cmd not found\n", 1);
		}
		if (execve(pipex->exec[i], pipex->cmd_args[i], pipex->envp) == -1)
		{
			free_pipes(pipex);
			error_exit(pipex, "Error exec\n", 1);
		}
	}
	else
	{
		free_pipes(pipex);
		error_exit(pipex, "Error exec\n", 1);
	}
}

void	pipeline(t_pipex *pipex, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		error_exit(pipex, "forking error\n", 1);
	}
	else if (pid == 0)
	{
		child_process(pipex, i);
	}
	if (pipex->input_file >= 0)
		close(pipex->input_file);
}

void	execute_pipeline(t_pipex *pipex)
{
	int		i;
	int		status;
	int		children;
	pid_t	pid;

	children = pipex->cmd_count;
	i = 0;
	open_pipes(pipex);
	while (i < pipex->cmd_count)
	{
		pipeline(pipex, i);
		i++;
	}
	if (pipex->output_file >= 0)
		close(pipex->output_file);
	cleanup_pipes(pipex);
	free_pipes(pipex);
	while (children > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid >= 0)
			children--;
		if (pid == -1)
			error_exit(pipex, NULL, 1);
	}
}

t_pipex	*init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		exit(1);
	get_paths(pipex, envp);
	pipex->cmd_count = (argc - 3 - pipex->here_doc);
	pipex->envp = envp;
	if (pipex->cmd_count < 2)
		error_exit(pipex, "Not enough arguments\n", 0);
	open_files(pipex, argv, argc);
	get_exec(pipex, argv);
	return (pipex);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;

	if (argc == 5)
	{
		pipex = init_pipex(argc, argv, envp);
		execute_pipeline(pipex);
		if (!pipex->inv_input)
			close(pipex->input_file);
		free_pipex(pipex);
	}
	else
		ft_putendl_fd("Incorrect number of arguments (must be exactly 4)\n", 2);
	return (0);
}
