/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:44:48 by jfita             #+#    #+#             */
/*   Updated: 2024/05/03 14:43:14 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_exec(t_pipex *pipex, char *cmd, int j)
{
	char	*exec;

	if (cmd)
	{
		if ((cmd[0] == '.' || cmd[0] == '/'))
		{
			pipex->exec[j] = ft_strdup(cmd);
			return ;
		}
	}
	if (!cmd)
		pipex->nb_paths++;
	if (pipex->envp_missing || pipex->envp_paths == NULL)
	{
		exec = ft_strdup(cmd);
		if (access(exec, F_OK | X_OK) == 0)
			pipex->exec[j] = exec;
		else
			(free(exec), error_exit(pipex, NULL, 127));
	}
	else
		parse_exec_two(pipex, cmd, j);
	if (!pipex->exec[j] && cmd)
		pipex->exec[j] = ft_strdup(cmd);
}

void	parse_exec_two(t_pipex *pipex, char *cmd, int j)
{
	int		i;
	char	*exec;

	i = -1;
	while (pipex->envp_paths[++i])
	{
		exec = ft_strjoin(pipex->envp_paths[i], cmd);
		if (exec)
		{
			if (access(exec, F_OK | X_OK) == 0)
			{
				pipex->exec[j] = exec;
				break ;
			}
			free(exec);
		}
	}
}

void	get_exec(t_pipex *pipex, char **argv)
{
	int	i;
	int	j;

	i = -1 + pipex->here_doc;
	j = 0;
	pipex->cmd_args = (char ***)ft_calloc(pipex->cmd_count + 1, sizeof(char *));
	if (!pipex->cmd_args)
		error_exit(pipex, "Error malloc get_exec\n", 1);
	pipex->exec = (char **)ft_calloc(pipex->cmd_count, sizeof(char *));
	if (!pipex->exec)
		error_exit(pipex, "Error malloc get_exec\n", 1);
	while (++i < pipex->cmd_count + pipex->here_doc)
	{
		pipex->cmd_args[i - pipex->here_doc] = ft_split(argv[i + 2], ' ');
		if (!pipex->cmd_args[i - pipex->here_doc])
			error_exit(pipex, "Error malloc get_exec\n", 1);
		parse_exec(pipex, pipex->cmd_args[i - pipex->here_doc][0], j);
		j++;
	}
}

void	get_paths(t_pipex *pipex, char **envp)
{
	int		i;
	char	*str;

	i = 0;
	if (!envp || !envp[i] || !envp[i][0])
	{
		pipex->envp_missing = true;
		return ;
	}
	while (envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
	{
		pipex->envp_missing = true;
		return ;
	}
	pipex->envp_paths = split(envp[i], ':');
	if (!pipex->envp_paths)
		error_exit(pipex, "Malloc fail in get_paths\n", 1);
	str = ft_strtrim(pipex->envp_paths[0], "PATH=");
	if (!str)
		error_exit(pipex, "Malloc fail in get_paths\n", 1);
	free(pipex->envp_paths[0]);
	pipex->envp_paths[0] = str;
}

void	check_hd(t_pipex *pipex, char **argv)
{
	if (!ft_strncmp(argv[1], "here_doc", 8))
		pipex->here_doc = 1;
	else
		pipex->here_doc = 0;
}
