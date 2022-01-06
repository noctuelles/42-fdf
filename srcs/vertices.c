/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:49:33 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/06 15:08:58 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>

static void	free_values(char **values)
{
	size_t	i;

	i = 0;
	while (values[i] != NULL)
		free(values[i++]);
	free(values);
}

static int	fill_from_values(int **vertices, char **values, unsigned int y)
{
	int	x;

	x = 0;
	while (values[x] != NULL)
	{
		vertices[y][x] = ft_atoi(values[x]);
		x++;
	}
	return (0);
}

int	**alloc_vertices(t_mlx_data *data)
{
	int		**vertices;
	size_t	i;

	vertices = (int **) malloc(data->nbr_line * sizeof(int *));
	if (!vertices)
		return (NULL);
	i = 0;
	while (i < nbr_line)
	{
		vertices[i] = (int *) malloc(data->line_len * sizeof(int));
		if (!vertices[i])
		{
			free_vertices(vertices, i);
			return (NULL);
		}
		i++;
	}
	return (vertices);
}

int	**fill_vertices(int fd, int **vertices)
{
	unsigned int	y;
	char			*line;
	char			**values;

	y = 0;
	while (read_line(fd, &line) != NULL)
	{
		values = ft_split(line, ' ');
		if (!values)
			return (NULL);
		fill_from_values(vertices, values, y);
		free_values(values);
		free(line);
		y++;
	}
	return (vertices);
}

void	free_vertices(int **vertices, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
		free(vertices[i++]);
	free(vertices);
}
