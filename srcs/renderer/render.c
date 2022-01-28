/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:05:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/28 11:54:21 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	compute_angle(t_mlx_data *data)
{
	if (data->curr_proj->last_alpha != data->curr_proj->alpha)
	{
		data->curr_proj->sin_alpha = sin(data->curr_proj->alpha);
		data->curr_proj->cos_alpha = cos(data->curr_proj->alpha);
		data->curr_proj->last_alpha = data->curr_proj->alpha;
	}
	else if (data->curr_proj->last_beta != data->curr_proj->beta)
	{
		data->curr_proj->sin_beta = sin(data->curr_proj->beta);
		data->curr_proj->cos_beta = cos(data->curr_proj->beta);
		data->curr_proj->last_alpha = data->curr_proj->beta;
	}
	else if (data->curr_proj->last_gamma != data->curr_proj->gamma)
	{
		data->curr_proj->sin_gamma = sin(data->curr_proj->gamma);
		data->curr_proj->cos_gamma = cos(data->curr_proj->gamma);
		data->curr_proj->last_gamma = data->curr_proj->gamma;
	}
}

void	rotate(t_vec3d *vec, t_mlx_data *data)
{
	t_vec3d	old;

	old = *vec;
	vec->y = old.y * data->curr_proj->cos_alpha
		+ old.z * data->curr_proj->sin_alpha;
	vec->z = -old.y * data->curr_proj->sin_alpha
		+ old.z * data->curr_proj->cos_alpha;
	vec->x = old.x * data->curr_proj->cos_beta
		+ vec->z * data->curr_proj->sin_beta;
	vec->z = -old.x * data->curr_proj->sin_beta
		+ vec->z * data->curr_proj->cos_beta;
	old = *vec;
	vec->x = old.x * data->curr_proj->cos_gamma
		- old.y * data->curr_proj->sin_gamma;
	vec->y = old.x * data->curr_proj->sin_gamma
		+ old.y * data->curr_proj->cos_gamma;
}

static inline void	compute_n_draw(t_mlx *fdf, t_vec2d p1, int x, int y)
{
	t_vec3d	vec3d;
	t_vec2d	p2;

	set_vec3d(&vec3d, x, y, fdf->data.vertices[y][x]);
	p2 = fdf->data.curr_proj->transform(fdf->data.tile_width, fdf->data.org,
			vec3d, &fdf->data);
	if ((p2.x > 200 && p2.x <= WIDTH) && (p2.y >= 0 && p2.y <= HEIGHT))
	{
		if (p2.color == p1.color)
			draw_line(fdf, p1, p2, p1.color);
		else
			draw_line_gradient(fdf, p1, p2);
	}
}

void	render(t_mlx *fdf)
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
			p1 = fdf->data.curr_proj->transform(fdf->data.tile_width,
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
