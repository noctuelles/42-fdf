/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:49:07 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/29 14:14:38 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_gradient(t_mlx *mlx)
{
	t_vec2d	rect;
	t_vec2d	pos;

	set_vec2d(&rect, 15, 15);
	set_vec2d(&pos, 80, 859);
	draw_full_rect(mlx, rect, pos, mlx->data.gradient[0]);
	set_vec2d(&pos, 120, 859);
	draw_full_rect(mlx, rect, pos, mlx->data.gradient[mlx->data.max_z - 1]);
}

void	draw_compass(t_mlx *mlx)
{
	t_vec3d	p[3];
	t_vec2d	p2d[4];

	set_vec3d(&p[0], 0, 0, 2 * mlx->data.z_scaling);
	set_vec3d(&p[1], 2, 0, 0);
	set_vec3d(&p[2], 0, 2, 0);
	set_vec2d(&p2d[0], 300, 900);
	p2d[1] = mlx->data.curr_proj->transform(30, p2d[0], p[0], &mlx->data);
	p2d[2] = mlx->data.curr_proj->transform(30, p2d[0], p[1], &mlx->data);
	p2d[3] = mlx->data.curr_proj->transform(30, p2d[0], p[2], &mlx->data);
	draw_line(mlx, p2d[0], p2d[1], CLR_YELLOW);
	draw_line(mlx, p2d[0], p2d[2], CLR_GREEN);
	draw_line(mlx, p2d[0], p2d[3], CLR_RED);
}
