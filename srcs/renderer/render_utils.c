/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:10:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/26 23:56:26 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_edges_outside(t_vec2d edges[3])
{
	if (edges[0].x <= 200)
		return (1);
	else if (edges[1].y > HEIGHT)
		return (1);
	else if (edges[2].x > WIDTH)
		return (1);
	else
		return (0);
}

t_vec2d	get_center(t_mlx_data *data, size_t tile_width)
{
	t_vec2d	center;
	t_vec2d	org_hud;
	t_vec3d	vec;

	vec.x = data->elems_line / 2;
	vec.y = data->nbr_lines / 2;
	vec.z = 0;
	set_vec2d(&org_hud, 200, 0);
	center = data->curr_proj->transform(tile_width, org_hud, vec, data);
	return (center);
}

size_t	setup_map(t_mlx_data *data, t_vec3d medges[4])
{
	t_vec2d	edges[3];
	t_vec2d	old_org;
	t_vec2d	iso_center;
	size_t	tile_width;

	tile_width = 1;
	set_vec2d(&old_org, 0, 0);
	while (tile_width < 2000)
	{
		iso_center = get_center(data, tile_width);
		set_vec2d(&data->org, 200 + (950 - iso_center.x), 500 - iso_center.y);
		edges[0] = data->curr_proj->transform(tile_width, data->org, medges[0], data);
		edges[1] = data->curr_proj->transform(tile_width, data->org, medges[1], data);
		edges[2] = data->curr_proj->transform(tile_width, data->org, medges[2], data);
		if (is_edges_outside(edges))
		{
			if (old_org.x != 0 && old_org.y != 0)
				set_vec2d(&data->org, old_org.x, old_org.y);
			return (tile_width - 1);
		}
		set_vec2d(&old_org, data->org.x, data->org.y);
		tile_width++;
	}
	return (tile_width);
}
