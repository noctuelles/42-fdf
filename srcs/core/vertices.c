/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:49:33 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/18 15:35:20 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

int	**alloc_vertices(size_t nbr_lines)
{
	int		**vertices;
	size_t	i;

	vertices = (int **) malloc((nbr_lines + 1) * sizeof(int *));
	if (!vertices)
		return (NULL);
	i = 0;
	while (i < (nbr_lines + 1))
		vertices[i++] = NULL;
	return (vertices);
}

static void	free_values(char **values)
{
	size_t	i;

	i = 0;
	while (values[i] != NULL)
		free(values[i++]);
	free(values);
}

void	free_vertices(int **vertices)
{
	size_t	i;

	i = 0;
	while (vertices[i] != NULL)
		free(vertices[i++]);
	free(vertices);
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
		if (data->vertices[y][x] > data->edges[0].z)
		{
			data->edges[0].x = x;
			data->edges[0].y = y;
			data->edges[0].z = data->vertices[y][x];
		}
		x++;
	}
	return (data->vertices);
}

int	**fill_vertices(int fd, t_mlx_data *data)
{
	char	*line;
	char	**values;
	int		y;

	y = 0;
	while(read_line(fd, &line))
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
	data->edges[1].x = 0;
	data->edges[1].y = data->nbr_lines - 1;
	data->edges[1].z = data->vertices[data->edges[1].y][0];
	data->edges[2].x = data->elems_line - 1;
	data->edges[2].y = data->nbr_lines - 1;
	data->edges[2].z = data->vertices[data->edges[2].y][data->edges[2].x];
	data->edges[3].x = data->elems_line - 1;
	data->edges[3].y = 0;
	data->edges[3].z = data->vertices[0][data->edges[3].x];
	return (data->vertices);
}
