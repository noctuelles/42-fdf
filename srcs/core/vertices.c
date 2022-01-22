/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:49:33 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/23 00:28:33 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

static void	free_values(char **values)
{
	size_t	i;

	i = 0;
	while (values[i] != NULL)
		free(values[i++]);
	free(values);
}

static size_t	get_elems_per_line(char **values)
{
	size_t	i;

	i = 0;
	while (values[i])
		i++;
	return (i);
}

static int	**fill_vertices_from_values(t_mlx_data *data, char **values, int y)
{
	int	x;

	x = 0;
	data->vertices[y] = (int *) malloc(data->elems_line * sizeof(int));
	if (!data->vertices[y])
	{
		free_values(values);
		return (NULL);
	}
	while (values[x] != NULL)
	{
		data->vertices[y][x] = ft_atoi(values[x]);
		x++;
	}
	return (data->vertices);
}

static void	set_edges(t_mlx_data *data)
{
	data->edges[0].x = 0;
	data->edges[0].y = data->nbr_lines - 1;
	data->edges[0].z = data->vertices[data->edges[0].y][0];
	data->edges[1].x = data->elems_line - 1;
	data->edges[1].y = data->nbr_lines - 1;
	data->edges[1].z = data->vertices[data->edges[1].y][data->edges[1].x];
	data->edges[2].x = data->elems_line - 1;
	data->edges[2].y = 0;
	data->edges[2].z = data->vertices[0][data->edges[2].x];
}

int	**fill_vertices(int fd, t_mlx_data *data)
{
	char	*line;
	char	**values;
	int		y;

	y = 0;
	while (read_line(fd, &line))
	{
		values = ft_split(line, ' ');
		if (!values)
			return (NULL);
		if (data->elems_line == 0)
			data->elems_line = get_elems_per_line(values);
		data->vertices = fill_vertices_from_values(data, values, y);
		if (!data->vertices)
			return (NULL);
		free_values(values);
		free(line);
		y++;
	}
	set_edges(data);
	return (data->vertices);
}
