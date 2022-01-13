/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:50:11 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/13 22:33:22 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	draw_hud_title(t_mlx *mlx, int y, uint32_t color, char *txt)
{
	size_t	len;
	int		x;

	len = strlen(txt);
	len = len * 6 - 1;
	x = (100 - len) + (len / 2);
	mlx_string_put(mlx->inst, mlx->wnd, x, y, color, txt);
}


void	draw_hud_bg(t_mlx *mlx)
{
	t_vec2d	rect;
	t_vec2d	pos;

	set_vec2d(&rect, 200, HEIGHT);
	set_vec2d(&pos, 0, 0);
	draw_full_rect(mlx, rect, pos, 0xff303030);
	set_vec2d(&pos, 2, 0);
	set_vec2d(&rect, rect.x - 4, 2);
	draw_full_rect(mlx, rect, pos, 0xffffffff);
	set_vec2d(&pos, pos.x, 700);
	draw_full_rect(mlx, rect, pos, 0xffffffff);
	set_vec2d(&pos, pos.x, 950);
	draw_full_rect(mlx, rect, pos, 0xffffffff);
	set_vec2d(&pos, pos.x, 998);
	draw_full_rect(mlx, rect, pos, 0xffffffff);
	set_vec2d(&rect, 2, HEIGHT);
	set_vec2d(&pos, 0, 0);
	draw_full_rect(mlx, rect, pos, 0xffffffff);
	set_vec2d(&pos, 200 - 2, pos.y);
	draw_full_rect(mlx, rect, pos, 0xffffffff);
}

void	draw_hud_static_text(t_mlx *mlx)
{
	draw_hud_title(mlx, 20, 0xffffffff, HUD_TXT);
	draw_hud_title(mlx, 85, 0xffffffff, TRANSLATION_TXT);
	draw_hud_title(mlx, 230, 0xffffffff, MAP_ZOOM);
	draw_hud_title(mlx, 330, 0xffffffff, Z_FACTOR);
	draw_hud_title(mlx, 430, 0xffffffff, ROTATE_MAP);
	draw_hud_title(mlx, 600, 0xffffffff, OTHERS);
	draw_hud_title(mlx, 720, 0xffffffff, MAP_INFO);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 750, 0xffffffff, FILE_NAME);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 770, 0xffffffff, VERTICES);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 790, 0xffffffff, TILE_SIZE);
	draw_hud_title(mlx, 970, 0xffffffff, ABOUT);
	draw_hud_title(mlx, 990, 0xffffffff, ABOUT_2);

	
	mlx_string_put(mlx->inst, mlx->wnd, 97, 124, 0xffffffff, "W");
	mlx_string_put(mlx->inst, mlx->wnd, 47, 174, 0xffffffff, "A");
	mlx_string_put(mlx->inst, mlx->wnd, 97, 174, 0xffffffff, "S");
	mlx_string_put(mlx->inst, mlx->wnd, 147, 174, 0xffffffff, "D");
	mlx_string_put(mlx->inst, mlx->wnd, 47, 274, 0xffffffff, "+");
	mlx_string_put(mlx->inst, mlx->wnd, 147, 274, 0xffffffff, "-");
	mlx_string_put(mlx->inst, mlx->wnd, 39, 374, 0xffffffff, "P-UP");
	mlx_string_put(mlx->inst, mlx->wnd, 139, 374, 0xffffffff, "P-DW");
	mlx_string_put(mlx->inst, mlx->wnd, 97, 471, 0xffffffff, "^");
	mlx_string_put(mlx->inst, mlx->wnd, 97, 475, 0xffffffff, "|");
	mlx_string_put(mlx->inst, mlx->wnd, 44, 524, 0xffffffff, "<-");
	mlx_string_put(mlx->inst, mlx->wnd, 94, 524, 0xffffffff, "DW");
	mlx_string_put(mlx->inst, mlx->wnd, 144, 524, 0xffffffff, "->");
	mlx_string_put(mlx->inst, mlx->wnd, 41, 654, 0xffffffff, "ESC");
	mlx_string_put(mlx->inst, mlx->wnd, 86, 654, 0xffffffff, "Quit");
}
