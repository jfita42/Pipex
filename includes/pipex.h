/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:24:26 by jfita             #+#    #+#             */
/*   Updated: 2024/05/01 17:47:39 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		index;
	int		input_file;
	int		output_file;
	int		**pipes;
	int		here_doc;
	bool	inv_input;
	bool	envp_missing;
	char	**envp_paths;
	char	**envp;
	char	***cmd_args;
	char	**exec;
	int		cmd_count;
	bool	is_path;
	int		nb_paths;
	int		nb_pipes;

}			t_pipex;

t_pipex		*init_pipex(int argc, char **argv, char **envp);
void		check_hd(t_pipex *pipex, char **argv);
void		get_paths(t_pipex *pipex, char **envp);
void		get_exec(t_pipex *pipex, char **argv);
void		parse_exec(t_pipex *pipex, char *cmd, int j);
void		parse_exec_two(t_pipex *pipex, char *cmd, int j);
void		exec(t_pipex *pipex, int i);

void		open_pipes(t_pipex *pipex);
void		pipeline(t_pipex *pipex, int i);
void		execute_pipeline(t_pipex *pipex);
void		cleanup_pipes(t_pipex *pipex);

void		child_process(t_pipex *pipex, int i);
void		first_child(t_pipex *pipex);
void		mid_child(t_pipex *pipex, int i);
void		all_but_last_child(t_pipex *pipex, int i);
void		last_child(t_pipex *pipex);

void		error_exit(t_pipex *pipex, char *msg, int err);

char		**split(char const *s, char c);
void		pipex_free_tab(char **tab);
void		open_files(t_pipex *pipex, char **argv, int argc);
void		free_pipex(t_pipex *pipex);
void		free_cmd_args(t_pipex *pipex);
void		free_exec(t_pipex *pipex);
void		free_paths(t_pipex *pipex);

void		here_doc(t_pipex *pipex, char **argv);
void		here_child(t_pipex *pipex, int *fd, char **argv);
bool		check_limiter(char c);

void		print_tab(t_pipex *pipex, char **tab);
void		free_pipes(t_pipex *pipex);

void		test_pipes(t_pipex *pipex);

#endif