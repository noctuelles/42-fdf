/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:05:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/24 14:12:14 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static inline void	compute_angle(t_mlx_data *data)
{
	if (data->last_alpha != data->alpha)
	{
		data->sin_alpha = sin(data->alpha);
		data->cos_alpha = cos(data->alpha);
		data->last_alpha = data->alpha;
	}
	else if (data->last_beta != data->beta)
	{
		data->sin_beta = sin(data->beta);
		data->cos_beta = cos(data->beta);
		data->last_alpha = data->beta;
	}
	else if (data->last_gamma != data->gamma)
	{
		data->sin_gamma = sin(data->gamma);
		data->cos_gamma = cos(data->gamma);
		data->last_gamma = data->gamma;
	}
}

static void	rotate(t_vec3d *vec, t_mlx_data *data)
{
	t_vec3d	old;

	old = *vec;
	vec->y = old.y * data->cos_alpha + old.z * data->sin_alpha;
	vec->z = -old.y * data->sin_alpha + old.z * data->cos_alpha;
	vec->x = old.x * data->cos_beta + vec->z * data->sin_beta;
	vec->z = -old.x * data->sin_beta + vec->z * data->cos_beta;
	old = *vec;
	vec->x = vec->x * data->cos_gamma - vec->y * data->sin_gamma;
	vec->y = vec->x * data->sin_gamma + vec->y * data->cos_gamma;
}

t_vec2d	transform_isometric(size_t tile_width, t_vec2d org, t_vec3d vec3d,
															t_mlx_data *data)
{
	t_vec2d	proj;

	vec3d.x *= tile_width;
	vec3d.y *= tile_width;
	proj.z = vec3d.z;
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

static inline void	compute_n_draw(t_mlx *fdf, t_vec2d p1, int x, int y)
{
	t_vec3d	vec3d;
	t_vec2d	p2;

	set_vec3d(&vec3d, x, y, fdf->data.vertices[y][x]);
	p2 = transform_isometric(fdf->data.tile_width, fdf->data.org, vec3d,
			&fdf->data);
	if ((p2.x > 200 && p2.x <= WIDTH) && (p2.y >= 0 && p2.y <= HEIGHT))
	{
		if (p2.color == p1.color)
			draw_line(fdf, p1, p2, p1.color);
		else
			draw_line_gradient(fdf, p1, p2);
	}
}

void	apply_isometric(t_mlx *fdf)
{
	t_vec3d			vec3d;
	t_vec2d			p1;
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < fdf->data.nbr_lines)
	{
		x = 0;
		while (x < fdf->data.elems_line)
		{
			set_vec3d(&vec3d, x, y, fdf->data.vertices[y][x]);
			p1 = transform_isometric(fdf->data.tile_width,
					fdf->data.org, vec3d, &fdf->data);
			if ((p1.x > 200 && p1.x <= WIDTH) && (p1.y >= 0 && p1.y <= HEIGHT))
			{
				if (x < fdf->data.elems_line - 1)
					compute_n_draw(fdf, p1, x + 1, y);
				if (y > 0)
					compute_n_draw(fdf, p1, x, y - 1);
			}
			x++;
		}
		y++;
	}
}
