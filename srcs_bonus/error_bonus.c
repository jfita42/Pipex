/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:33:36 by jfita             #+#    #+#             */
/*   Updated: 2024/05/02 14:07:22 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_tab(t_pipex *pipex, char **tab)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		ft_printf("tab[%d]: %s\n", i, tab[i]);
		i++;
	}
}

void	error_exit(t_pipex *pipex, char *msg, int err)
{
	if (msg)
		perror(msg);
	free_pipex(pipex);
	exit(err);
}
