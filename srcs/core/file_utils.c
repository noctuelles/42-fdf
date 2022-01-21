/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:17:09 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/21 15:26:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>

static ssize_t	read_fd(int fd, char *buffer, ssize_t *rdead, size_t index)
{
	if (index == 0)
		*rdead = read(fd, buffer, 4096);
	if (*rdead < 0)
		return (0);
	return (*rdead);
}

char	*read_line(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line);
}

/* Instead of using get_next_line to count line, i use a dedicated fonction */

size_t	get_file_nbr_lines(const char *path)
{
	size_t	i;
	int		fd;
	size_t	nbr_lines;
	ssize_t	rdead;
	char	buffer[4096];

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	i = 0;
	nbr_lines = 0;
	ft_memset(&buffer, 0, 4096);
	while (read_fd(fd, buffer, &rdead, i))
	{
		while (i < (size_t)(rdead - 1) && buffer[i] != '\n')
			i++;
		if (buffer[i++] == '\n')
			nbr_lines++;
		else
			i = 0;
	}
	close(fd);
	return (nbr_lines);
}
