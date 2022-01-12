/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:14:14 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/12 15:20:38 by plouvel          ###   ########.fr       */
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

int	**parse_map(const char *path, t_mlx_data *data)
{
	int	fd;

	data->nbr_lines = get_file_nbr_lines(path);
	if (data->nbr_lines == 0)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	data->vertices = alloc_vertices(data->nbr_lines);
	if (!data->vertices)
		return (NULL);
	data->vertices = fill_vertices(fd, data);
	if (!data->vertices)
	{
		free_vertices(data->vertices);
		return (NULL);
	}
	close(fd);
	return (data->vertices);
}
