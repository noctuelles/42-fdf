/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ortho.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:55:33 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/25 14:35:27 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static inline void	compute_angle(t_mlx_data *data)
{
	if (data->last_gamma != data->gamma)
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
	vec->x = vec->x * data->cos_gamma - vec->y * data->sin_gamma;
	vec->y = old.x * data->sin_gamma + vec->y * data->cos_gamma;
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
	compute_angle(data);
	rotate(&vec3d, data);
	proj.x = vec3d.x + org.x;
	proj.y = vec3d.y + org.y;
	return (proj);
}

static inline void	compute_n_draw(t_mlx *fdf, t_vec2d p1, int x, int y)
{
	t_vec3d	vec3d;
	t_vec2d	p2;

	set_vec3d(&vec3d, x, y, fdf->data.vertices[y][x]);
	p2 = transform_ortho(fdf->data.tile_width, fdf->data.org, vec3d,
			&fdf->data);
	if ((p2.x > 200 && p2.x <= WIDTH) && (p2.y >= 0 && p2.y <= HEIGHT))
	{
		if (p2.color == p1.color)
			draw_line(fdf, p1, p2, p1.color);
		else
			draw_line_gradient(fdf, p1, p2);
	}
}

void	apply_ortho(t_mlx *fdf)
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
			p1 = transform_ortho(fdf->data.tile_width,
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
