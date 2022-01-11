/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:05:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/11 18:34:13 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
/*
void	apply_isometric(t_mlx_data *data)
{
	t_vec3d	*vec3d;
	t_list	*vertices;
	size_t	tile_height;
	int		old_x;

	vertices = data->vertices;
	while (vertices != NULL)
	{
		vec3d = (t_vec3d *) vertices->content;
		tile_height = data->tile_width / 2;
		old_x = vec3d->x;
		vec3d->x = (vec3d->x - vec3d->y)  * (data->tile_width / 2);
		vec3d->y = (-vec3d->z * (tile_height / 2)) +
										(old_x + vec3d->y) * (tile_height / 2);
		vertices = vertices->next;
	}
}

t_list	*search_vertices(t_mlx_data data, int x, int y)
{
	size_t	i;
	size_t	nbr;

	i = 0;
	nbr = x + (y * data.elems_line);
	while (i++ < nbr)
		data.vertices = data.vertices->next;
	return (data.vertices);
}

void	render_isometric(t_mlx *fdf)
{
	t_list	*vertices;
	t_vec3d	vec3d;

	vertices = fdf->data.vertices;
	while (vertices != NULL)
	{
		vec3d = *(t_vec3d *) vertices->content;
		put_pixel(fdf, vec3d.x + 800, vec3d.y + 300, 0xffffffff);
		vertices = vertices->next;
	}
}
*/
