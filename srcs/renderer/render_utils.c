/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:10:25 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/29 16:00:27 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline int	is_outside(t_vec2d vec2d)
{
	if (vec2d.x <= 200 || vec2d.x >= WIDTH || vec2d.y <= 0 || vec2d.y >= HEIGHT)
		return (1);
	return (0);
}

static int	check_map(t_mlx_data *data, size_t tile_width)
{
	t_vec3d	vec3d;
	t_vec2d	vec2d;

	vec3d.y = 0;
	while (vec3d.y < data->nbr_lines)
	{
		vec3d.x = 0;
		while (vec3d.x < data->elems_line)
		{
			vec3d.z = data->vertices[vec3d.y][vec3d.x];
			vec2d = data->curr_proj->transform(tile_width, data->curr_proj->org,
					vec3d, data);
			if (is_outside(vec2d))
				return (1);
			vec3d.x++;
		}
		vec3d.y++;
	}
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

static inline void	set_map_center(t_mlx_data *data, size_t tile_width)
{
	t_vec2d	iso_center;

	iso_center = get_center(data, tile_width);
	set_vec2d(&data->curr_proj->org, 1150 - iso_center.x, 500 - iso_center.y);
}

size_t	setup_map(t_mlx_data *data)
{
	t_vec2d	old_org;
	size_t	tile_width;

	tile_width = 1;
	set_vec2d(&old_org, 0, 0);
	while (tile_width < 2000)
	{
		set_map_center(data, tile_width);
		if (check_map(data, tile_width))
		{
			if (old_org.x != 0 && old_org.y != 0)
				set_vec2d(&data->curr_proj->org, old_org.x, old_org.y);
			if (tile_width != 1)
				return (tile_width - 1);
			else
				return (tile_width);
		}
		set_vec2d(&old_org, data->curr_proj->org.x, data->curr_proj->org.y);
		tile_width++;
	}
	return (tile_width);
}
