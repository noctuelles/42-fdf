/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:49:33 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/27 12:50:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

static int	free_values(char **values)
{
	size_t	i;

	i = 0;
	while (values[i] != NULL)
		free(values[i++]);
	free(values);
	return (-1);
}

static size_t	get_elems_per_line(char **values)
{
	size_t	i;
	size_t	elems;

	i = 0;
	elems = 0;
	while (values[i])
	{
		if (values[i][0] != ' ' && values[i][0] != '\n')
			elems++;
		i++;
	}
	return (elems);
}

static int	fill_vertices_from_values(t_mlx_data *data, char **values, int y)
{
	int	x;

	x = 0;
	data->vertices[y] = (int *) malloc(data->elems_line * sizeof(int));
	if (!data->vertices[y])
		return (free_values(values));
	while (values[x] != NULL)
	{
		if (values[x][0] != ' ' && values[x][0] != '\n')
		{
			if (!ft_isdigit(values[x][0]) && values[x][0] != '-')
				return (free_values(values));
			data->vertices[y][x] = ft_atoi(values[x]);
			if (data->vertices[y][x] > data->max_z)
				data->max_z = data->vertices[y][x];
			else if (data->vertices[y][x] < data->min_z)
				data->min_z = data->vertices[y][x];
		}
		x++;
	}
	return (0);
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

int	fill_vertices(int fd, t_mlx_data *data)
{
	char	*line;
	char	**values;
	int		y;

	y = 0;
	while (read_line(fd, &line))
	{
		values = ft_split(line, ' ');
		free(line);
		if (!values)
			return (-1);
		if (data->elems_line == 0)
			data->elems_line = get_elems_per_line(values);
		if (fill_vertices_from_values(data, values, y) == -1)
			return (-1);
		free_values(values);
		y++;
	}
	set_edges(data);
	return (0);
}
