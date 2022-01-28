/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:42:43 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/28 19:04:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec2d	transform_iso(size_t tile_width, t_vec2d org, t_vec3d vec3d,
															t_mlx_data *data)
{
	t_vec2d	proj;

	vec3d.x *= tile_width;
	vec3d.y *= tile_width;
	if (vec3d.z < 0)
		proj.color = data->gradient[ft_abs(data->min_z) - ft_abs(vec3d.z)];
	else if (vec3d.z == 0)
		proj.color = data->gradient[ft_abs(data->min_z)];
	else
		proj.color = data->gradient[ft_abs(data->min_z) + (vec3d.z - 1)];
	vec3d.z *= tile_width / data->z_scaling;
	compute_angle(data);
	rotate(&vec3d, data);
	proj.x = (vec3d.x - vec3d.y) * data->cos_theta;
	proj.y = -vec3d.z + (vec3d.x + vec3d.y) * data->sin_theta;
	proj.x += org.x;
	proj.y += org.y;
	return (proj);
}

t_vec2d	transform_ortho(size_t tile_width, t_vec2d org, t_vec3d vec3d,
		t_mlx_data *data)
{
	t_vec2d	proj;

	vec3d.x *= tile_width;
	vec3d.y *= tile_width;
	if (vec3d.z < 0)
		proj.color = data->gradient[ft_abs(data->min_z) - ft_abs(vec3d.z)];
	else if (vec3d.z == 0)
		proj.color = data->gradient[ft_abs(data->min_z)];
	else
		proj.color = data->gradient[ft_abs(data->min_z) + (vec3d.z - 1)];
	vec3d.z = 0;
	compute_angle(data);
	rotate(&vec3d, data);
	proj.x = vec3d.x + org.x;
	proj.y = vec3d.y + org.y;
	return (proj);
}
