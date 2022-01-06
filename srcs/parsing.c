/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:14:14 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/06 15:04:21 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <fcntl.h>

/*
 *	Verification of the file could be implemented.
 */

int	**parse_map(const char *path, t_mlx_data *data)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	get_file_infos(fd, data);
	data->vertices = alloc_vertices(data);
	if (!data->vertices)
		return (NULL);
	data->vertices = fill_vertices(data);
	if (!data->vertices)
		return (NULL);
	close(fd);
	return (vertices);
}
