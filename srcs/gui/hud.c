/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:50:11 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/25 13:21:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

/* draw_hud_title: draw text centered compared to the hud. */

static void	draw_hud_title(t_mlx *mlx, int y, uint32_t color, char *txt)
{
	size_t	len;
	int		x;

	len = ft_strlen(txt);
	len = len * 6 - 1;
	x = (100 - len) + (len / 2);
	mlx_string_put(mlx->inst, mlx->wnd, x, y, color, txt);
}

/* draw_hud_bg: draw the static colors, the background. */

void	draw_hud_bg(t_mlx *mlx)
{
	t_vec2d	rect;
	t_vec2d	pos;

	set_vec2d(&rect, 200, HEIGHT);
	set_vec2d(&pos, 0, 0);
	draw_full_rect(mlx, rect, pos, 0xff303030);
	set_vec2d(&pos, 2, 0);
	set_vec2d(&rect, rect.x - 4, 2);
	draw_full_rect(mlx, rect, pos, CLR_WHITE);
	set_vec2d(&pos, pos.x, 700);
	draw_full_rect(mlx, rect, pos, CLR_WHITE);
	set_vec2d(&pos, pos.x, 950);
	draw_full_rect(mlx, rect, pos, CLR_WHITE);
	set_vec2d(&pos, pos.x, 998);
	draw_full_rect(mlx, rect, pos, CLR_WHITE);
	set_vec2d(&rect, 2, HEIGHT);
	set_vec2d(&pos, 0, 0);
	draw_full_rect(mlx, rect, pos, CLR_WHITE);
	set_vec2d(&pos, 200 - 2, pos.y);
	draw_full_rect(mlx, rect, pos, CLR_WHITE);
	draw_gradient(mlx);
}

/* draw_key_static_text: draw all the static text of the hud. */

static void	draw_key_static_text(t_mlx *mlx)
{
	mlx_string_put(mlx->inst, mlx->wnd, 97, 124, CLR_WHITE, "W");
	mlx_string_put(mlx->inst, mlx->wnd, 47, 174, CLR_WHITE, "A");
	mlx_string_put(mlx->inst, mlx->wnd, 97, 174, CLR_WHITE, "S");
	mlx_string_put(mlx->inst, mlx->wnd, 147, 174, CLR_WHITE, "D");
	mlx_string_put(mlx->inst, mlx->wnd, 47, 274, CLR_WHITE, "+");
	mlx_string_put(mlx->inst, mlx->wnd, 147, 274, CLR_WHITE, "-");
	mlx_string_put(mlx->inst, mlx->wnd, 39, 374, CLR_WHITE, "P-UP");
	mlx_string_put(mlx->inst, mlx->wnd, 139, 374, CLR_WHITE, "P-DW");
	mlx_string_put(mlx->inst, mlx->wnd, 97, 471, CLR_WHITE, "^");
	mlx_string_put(mlx->inst, mlx->wnd, 97, 475, CLR_WHITE, "|");
	mlx_string_put(mlx->inst, mlx->wnd, 44, 524, CLR_WHITE, "<-");
	mlx_string_put(mlx->inst, mlx->wnd, 94, 524, CLR_WHITE, "DW");
	mlx_string_put(mlx->inst, mlx->wnd, 144, 524, CLR_WHITE, "->");
	mlx_string_put(mlx->inst, mlx->wnd, 42, 634, CLR_WHITE, "ALT");
	mlx_string_put(mlx->inst, mlx->wnd, 139, 634, CLR_WHITE, "CRTL");
	mlx_string_put(mlx->inst, mlx->wnd, 41, 924, CLR_WHITE, "ESC");
	mlx_string_put(mlx->inst, mlx->wnd, 148, 924, CLR_WHITE, "P");
	mlx_string_put(mlx->inst, mlx->wnd, 40, 893, CLR_WHITE, "Quit");
	mlx_string_put(mlx->inst, mlx->wnd, 123, 893, CLR_WHITE, "Iso/Ortho");
}

static void	draw_hud_integer(t_mlx *fdf, int x, int y, int i)
{
	char	*str;

	str = ft_itoa(i);
	if (!str)
		return ;
	mlx_string_put(fdf->inst, fdf->wnd, x, y, CLR_WHITE, str);
	free(str);
}

void	draw_hud_static_text(t_mlx *mlx)
{
	draw_hud_title(mlx, 20, CLR_WHITE, HUD_TXT);
	draw_hud_title(mlx, 85, CLR_WHITE, TRANSLATION_TXT);
	draw_hud_title(mlx, 230, CLR_WHITE, MAP_ZOOM);
	draw_hud_title(mlx, 330, CLR_WHITE, Z_FACTOR);
	draw_hud_title(mlx, 430, CLR_WHITE, ROTATE_MAP);
	draw_hud_title(mlx, 580, CLR_WHITE, OTHERS);
	draw_hud_title(mlx, 720, CLR_WHITE, MAP_INFO);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 750, CLR_WHITE, FILE_NAME);
	mlx_string_put(mlx->inst, mlx->wnd, 80, 750, CLR_WHITE,
		mlx->data.file_name);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 770, CLR_WHITE, VERTICES);
	draw_hud_integer(mlx, 80, 770, mlx->data.nbr_vertices);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 790, CLR_WHITE, TILE_SIZE);
	draw_hud_integer(mlx, 80, 790, mlx->data.tile_width);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 810, CLR_WHITE, ORG_X);
	draw_hud_integer(mlx, 80, 810, mlx->data.org.x);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 830, CLR_WHITE, ORG_Y);
	draw_hud_integer(mlx, 80, 830, mlx->data.org.y);
	mlx_string_put(mlx->inst, mlx->wnd, 5, 850, CLR_WHITE, Z_OFFSET);
	draw_hud_integer(mlx, 80, 850, -(mlx->data.z_scaling - 7));
	mlx_string_put(mlx->inst, mlx->wnd, 5, 870, CLR_WHITE, GRADIENT);
	mlx_string_put(mlx->inst, mlx->wnd, 103, 870, CLR_WHITE, TO);
	draw_hud_title(mlx, 970, CLR_WHITE, ABOUT);
	draw_hud_title(mlx, 990, CLR_YELLOW, ABOUT_2);
	draw_key_static_text(mlx);
}
