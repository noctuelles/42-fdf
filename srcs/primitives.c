/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:47:15 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/13 18:49:29 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_rect(t_mlx *mlx, t_vec2d rect, t_vec2d pos, uint32_t color)
{
	t_vec2d	left_line[2];
	t_vec2d	right_line[2];
	t_vec2d	top_line[2];
	t_vec2d	bottom_line[2];

	left_line[0].x = pos.x;
	left_line[0].y = pos.y;
	left_line[1].x = pos.x;
	left_line[1].y = pos.y + rect.y;
	draw_line(mlx, left_line[0], left_line[1], color);
	right_line[0].x = pos.x + rect.x - 1;
	right_line[0].y = pos.y;
	right_line[1].x = pos.x + rect.x - 1;
	right_line[1].y = pos.y + rect.y;
	draw_line(mlx, right_line[0], right_line[1], color);
	top_line[0].x = pos.x + 1;
	top_line[0].y = pos.y;
	top_line[1].x = pos.x + rect.x;
	top_line[1].y = pos.y;
	draw_line(mlx, top_line[0], top_line[1], color);
	bottom_line[0].x = pos.x + 1;
	bottom_line[0].y = pos.y + rect.y - 1;
	bottom_line[1].x = pos.x + rect.x;
	bottom_line[1].y = pos.y + rect.y - 1;
	draw_line(mlx, bottom_line[0], bottom_line[1], color);
}

void	draw_full_rect(t_mlx *mlx, t_vec2d rect, t_vec2d pos, uint32_t color)
{
	t_vec2d			draw_vec;
	unsigned int	end_y;

	end_y = pos.y + rect.y;
	draw_vec.x = pos.x + rect.x;
	draw_vec.y = pos.y;
	while (draw_vec.y < end_y)
	{
		draw_line(mlx, pos, draw_vec, color);
		draw_vec.y++;
		pos.y++;
	}
}
