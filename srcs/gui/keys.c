/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:18:54 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/18 15:19:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_key(t_mlx *mlx, t_vec2d pos, char *txt_key)
{
	t_vec2d outside_rect;
	t_vec2d	inner_rect;
	t_vec2d	inner_rect_pos;
	t_key	key;

	outside_rect.x = 40;
	outside_rect.y = 40;
	inner_rect.x = 28;
	inner_rect.y = 28;
	inner_rect_pos.x = pos.x + 6;
	inner_rect_pos.y = pos.y + 6;
	draw_full_rect(mlx, outside_rect, pos, 0xffc0c0c0);
	draw_full_rect(mlx, inner_rect, inner_rect_pos, 0xff000000);
	draw_line(mlx, pos, inner_rect_pos, 0xff303030);
	set_vec2d(&pos, pos.x + 39, pos.y);
	set_vec2d(&inner_rect_pos, inner_rect_pos.x + 27, inner_rect_pos.y);
	draw_line(mlx, pos, inner_rect_pos, 0xff303030);
	set_vec2d(&pos, pos.x - 39, pos.y + 39);
	set_vec2d(&inner_rect_pos, inner_rect_pos.x - 27, inner_rect_pos.y + 27);
	draw_line(mlx, pos, inner_rect_pos, 0xff303030);
	set_vec2d(&pos, pos.x + 39, pos.y);
	set_vec2d(&inner_rect_pos, inner_rect_pos.x + 27, inner_rect_pos.y);
	draw_line(mlx, pos, inner_rect_pos, 0xff303030);
}

static void	draw_keys_quad(t_mlx *mlx)
{
	t_vec2d	pos;

	set_vec2d(&pos, 80, 100);
	draw_key(mlx, pos, "W");
	set_vec2d(&pos, 30, 150);
	draw_key(mlx, pos, "A");
	set_vec2d(&pos, 80, 150);
	draw_key(mlx, pos, "S");
	set_vec2d(&pos, 130, 150);
	draw_key(mlx, pos, "D");
	set_vec2d(&pos, 80, 450);
	draw_key(mlx, pos, "^");
	set_vec2d(&pos, 30, 500);
	draw_key(mlx, pos, "<-");
	set_vec2d(&pos, 80, 500);
	draw_key(mlx, pos, "DW");
	set_vec2d(&pos, 130, 500);
	draw_key(mlx, pos, "->");
}

void	draw_keys(t_mlx *mlx)
{
	t_vec2d	pos;

	draw_keys_quad(mlx);
	set_vec2d(&pos, 30, 250);
	draw_key(mlx, pos, "+");
	set_vec2d(&pos, 130, 250);
	draw_key(mlx, pos, "-");
	set_vec2d(&pos, 30, 350);
	draw_key(mlx, pos, "P-UP");
	set_vec2d(&pos, 130, 350);
	draw_key(mlx, pos, "P-DW");
	set_vec2d(&pos, 30, 630);
	draw_key(mlx, pos, "ESC");
}
