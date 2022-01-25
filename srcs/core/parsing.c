/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:14:14 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/25 14:19:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>

/*
 *	Verification of the file could be implemented.
 */

int	**parse_map(char *path, t_mlx_data *data)
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
	if (fill_vertices(fd, data) == -1)
	{
		free_vertices(data->vertices);
		return (NULL);
	}
	data->file_name = path;
	data->nbr_vertices = data->elems_line * data->nbr_lines;
	if (ft_strlen(data->file_name) > 19)
		data->file_name[19] = '\0';
	close(fd);
	return (data->vertices);
}
