/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:49:07 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/24 15:53:01 by plouvel          ###   ########.fr       */
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
