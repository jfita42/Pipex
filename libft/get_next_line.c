/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfita <jfita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:26:50 by jfita             #+#    #+#             */
/*   Updated: 2024/04/30 15:22:33 by jfita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read(int fd, char *save)
{
	char	*tmp;
	int		readed;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	readed = 1;
	if (!save)
	{
		save = malloc(sizeof(char) * 1);
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	while (!ft_strchr(save, '\n') && readed != 0)
	{
		readed = read(fd, tmp, BUFFER_SIZE);
		if (readed == -1)
			return (free(tmp), free(save), NULL);
		tmp[readed] = '\0';
		save = ft_strjoin_free(save, tmp);
	}
	return (free(tmp), save);
}

char	*ft_get_line(char *save)
{
	char	*line;

	int (i) = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		line = ft_strndup(save, i + 1);
	else
		line = ft_strndup(save, i);
	return (line);
}

char	*ft_clean_save(char *save)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	len = ft_strlen(save);
	if (!save[i])
		return (free(save), NULL);
	new = ft_strndup((save + i + 1), (len - i));
	if (new)
		free(save);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	save = ft_read(fd, save);
	if (!save || save[0] == 0)
		return (free(save), save = NULL, NULL);
	line = ft_get_line(save);
	if (!line || line[0] == 0)
		return (free(line), free(save), NULL);
	save = ft_clean_save(save);
	if (save && save[0] == 0)
		(free(save), save = NULL);
	return (line);
}
