/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:05:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/19 23:17:42 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	rotate(t_vec3d *vec, double alpha, double beta, double gamma)
{
	double	cos_cptd;
	double	sin_cptd;
	t_vec3d	old;

	old = *vec;
	vec->y = old.y * cos(alpha) + old.z * sin(alpha);
	vec->z = -old.y * sin(alpha) + old.z * cos(alpha);
	vec->x = old.x * cos(beta) + vec->z * sin(beta);
	vec->z = -old.x * sin(beta) + vec->z * cos(beta);
	old = *vec;
	vec->x = vec->x * cos(gamma) - vec->y * sin(gamma);
	vec->y = vec->x * sin(gamma) + vec->y * cos(gamma);
}

t_vec2d	transform_isometric(size_t tile_width, t_vec2d org, t_vec3d vec3d, t_mlx_data *data)
{
	t_vec2d	proj;

	vec3d.x *= tile_width;
	vec3d.y *= tile_width;
	vec3d.z *= tile_width / data->z_scaling;
	rotate(&vec3d, data->alpha, data->beta, data->gamma);
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
	p2 = transform_isometric(fdf->data.tile_width, fdf->data.org, vec3d, &fdf->data);
	if ((p2.x > 200 && p2.x <= WIDTH) && (p2.y >= 0 && p2.y <= HEIGHT))
		draw_line(fdf, p1, p2, 0xffffffff);
}

/* Instead of using get_next_line to count line, i use a dedicated fonction */

void	apply_isometric(t_mlx *fdf)
{
	t_vec3d	vec3d;
	t_vec2d	p1;
	int		x;
	int		y;

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
