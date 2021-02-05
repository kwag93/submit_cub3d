/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkwag <bkwag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 13:40:41 by hyunyoo           #+#    #+#             */
/*   Updated: 2021/01/09 14:58:37 by bkwag            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	check_newline(char *backup)
{
	int i;

	i = 0;
	while (backup[i])
	{
		if (backup[i] == '\n')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	split_line(char **backup, char **line, int newline_idx)
{
	int		length;
	char	*after;

	(*backup)[newline_idx] = '\0';
	*line = ft_strdup_gnl(*backup);
	length = ft_strlen_gnl(*backup + newline_idx + 1);
	if (!length)
	{
		free(*backup);
		*backup = 0;
		return (1);
	}
	after = ft_strdup_gnl(*backup + newline_idx + 1);
	free(*backup);
	*backup = after;
	return (1);
}

int	return_all(char **backup, char **line, int r_size)
{
	int	newline_idx;

	if (r_size < 0)
		return (-1);
	if (*backup && (newline_idx = check_newline(*backup)) >= 0)
		return (split_line(backup, line, newline_idx));
	else if (*backup)
	{
		*line = *backup;
		*backup = 0;
		return (0);
	}
	*line = ft_strdup_gnl("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*result[OPEN_MAX];
	int			r_size;
	int			newline_idx;

	if (fd < 0 || fd >= OPEN_MAX || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((r_size = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[r_size] = '\0';
		result[fd] = ft_strjoin_gnl(result[fd], buffer);
		if ((newline_idx = check_newline(result[fd])) >= 0)
			return (split_line(&result[fd], line, newline_idx));
	}
	return (return_all(&result[fd], line, r_size));
}
