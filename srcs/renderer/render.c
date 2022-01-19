/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:05:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/19 14:15:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	rotate_z(t_vec3d *point, double angle)
{
	int	x;
	int	y;

	x = point->x;
	y = point->y;
	point->x = x * cos(angle) - y * sin(angle);
	point->y = y * cos(angle) + x * sin(angle);
}

void	rotate_y(t_vec3d *point, double angle)
{
	int	x;
	int	z;

	z = point->z;
	x = point->x;
	point->x = x * cos(angle) - z * sin(angle);
	point->z = z * cos(angle) + x * sin(angle);
}

void	rotate_x(t_vec3d *point, double angle)
{
	int	y;
	int	z;
	z = point->z;
	y = point->y;
	point->y = y * cos(angle) - z * sin(angle);
	point->z = z * cos(angle) + y * sin(angle);
}

t_vec2d	transform_isometric(size_t tile_width, t_vec2d org, t_vec3d vec3d, t_mlx_data *data)
{
	t_vec2d	proj;

	rotate_z(&vec3d, data->angle2);
	proj.x = (vec3d.x - vec3d.y) * (tile_width / 2);
	proj.y = (-vec3d.z * data->z_scaling) + (vec3d.x + vec3d.y) * (tile_width / 4);
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
