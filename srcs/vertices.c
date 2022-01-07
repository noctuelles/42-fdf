/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:49:33 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/07 19:05:28 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static t_vec3d	*alloc_vec3d(int x, int y, int z)
{
	t_vec3d	*vec3d;

	vec3d = (t_vec3d *) malloc(sizeof(t_vec3d));
	if (!vec3d)
		return (NULL);
	vec3d->x = x;
	vec3d->y = y;
	vec3d->z = z;
	return (vec3d);
}

static void	lst_addback(t_list *elem, t_list **lst, t_list **beg)
{
	if (!*lst)
	{
		*lst = elem;
		*beg = elem;
	}
	else
	{
		(*lst)->next = elem;
		*lst = elem;
	}
}

static t_list	*fill_vertices_from_line(char *line, t_list **lst, int *x, int y)
{
	size_t			i;
	int				z;
	t_list			*elem;
	static t_list	*vertices = NULL;

	i = 0;
	*x = 0;
	z = 0;
	while (line[i] && line[i] != '\n')
	{
		z = ft_atoi(&line[i]);
		elem = ft_lstnew((void *) alloc_vec3d(*x, y, z));
		if (!elem)
			return (NULL);
		lst_addback(elem, &vertices, lst);
		while (ft_isdigit(line[i]))
			i++;
		while (line[i] == ' ')
			i++;
		*x += 1;
	}
	return (*lst);
}

t_list	*fill_vertices(int fd, t_mlx_data *data)
{
	char	*line;
	int		x;
	int		y;
	t_list	*vertices;

	y = 0;
	vertices = NULL;
	while (read_line(fd, &line) != NULL)
	{
		vertices = fill_vertices_from_line(line, &vertices, &x, y);
		if (!vertices)
			return (NULL);
		free(line);
		y++;
	}
	data->nbr_line = y;
	data->elems_line = x;
	return (vertices);
}

#include <stdio.h>

void	print_vertices(t_list *lst)
{
	t_vec3d	vec3d;

	while (lst)
	{
		vec3d = *(t_vec3d *) lst->content;
		printf("x : %d	y : %d	z : %d\n", vec3d.x, vec3d.y, vec3d.z);
		lst = lst->next;
	}
}
