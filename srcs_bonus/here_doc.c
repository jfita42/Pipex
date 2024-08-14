/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:31:41 by jfita             #+#    #+#             */
/*   Updated: 2024/05/02 14:20:11 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc(t_pipex *pipex, char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit(pipex, "Error Pipe HereDoc", errno);
	pid = fork();
	if (pid == -1)
		error_exit(pipex, "Fork Error HereDoc", errno);
	if (pid == 0)
	{
		here_child(pipex, fd, argv);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		pipex->input_file = fd[0];
	}
}

void	here_child(t_pipex *pipex, int *fd, char **argv)
{
	int		len;
	char	*line;

	len = ft_strlen(argv[2]);
	close(fd[0]);
	ft_printf("Heredoc> ");
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, argv[2], len) == 0 && check_limiter(line[len]))
			break ;
		ft_printf("Heredoc> ");
		ft_putstr_fd(line, fd[1]);
		free(line);
		line = NULL;
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close(pipex->output_file);
	free_pipex(pipex);
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

bool	check_limiter(char c)
{
	if (c == '\t' || c == '\n' || c == 32 || c == '\0')
		return (true);
	else
		return (false);
}
