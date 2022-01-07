/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:14:14 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/07 15:57:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/*
 *	Verification of the file could be implemented.
 */

char	*read_line(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line);
}

t_list	*parse_map(const char *path, t_mlx_data *data)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	data->vertices = fill_vertices(fd, data);
	close(fd);
	return (data->vertices);
}
