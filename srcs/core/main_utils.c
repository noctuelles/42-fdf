/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:49:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/27 12:25:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

/* key_handler_change_proj() is about the keys that change the current proj-
 * -jection. */

static void	key_handler_change_proj(int keycode, t_mlx *fdf)
{
	if (keycode == K_P && fdf->data.curr_proj->id == ISO)
		set_projection(&fdf->data, ORTHO);
	else if (keycode == K_P && fdf->data.curr_proj->id == ORTHO)
		set_projection(&fdf->data, ISO);
	else if (keycode == 0x6d)
	{
		fdf->data.curr_proj->alpha = 0;
		fdf->data.curr_proj->beta = 0;
		fdf->data.curr_proj->gamma = 0;
	}
}

/* Explicit function name. */

static void	key_handler_do_rotation(int keycode, t_mlx *fdf)
{
	if (keycode == K_UP)
		fdf->data.curr_proj->alpha += 0.05;
	else if (keycode == K_DOWN)
		fdf->data.curr_proj->alpha -= 0.05;
	else if (keycode == K_RIGHT)
		fdf->data.curr_proj->beta += 0.05;
	else if (keycode == K_LEFT)
		fdf->data.curr_proj->beta -= 0.05;
	if (keycode == K_E)
		fdf->data.curr_proj->gamma += 0.05;
	else if (keycode == K_R)
		fdf->data.curr_proj->gamma -= 0.05;
}

/* Explicit function name. */

static void	key_handler_do(int keycode, t_mlx *fdf)
{
	if (keycode == K_PLUS)
		fdf->data.tile_width += 1;
	else if (keycode == K_MINUS)
		fdf->data.tile_width -= 1;
	else if (keycode == K_W)
		fdf->data.org.y -= 8;
	else if (keycode == K_S)
		fdf->data.org.y += 8;
	else if (keycode == K_A)
		fdf->data.org.x -= 8;
	else if (keycode == K_D)
		fdf->data.org.x += 8;
	else if (keycode == K_PGUP && fdf->data.curr_proj->id == ISO)
		fdf->data.z_scaling -= 0.5;
	else if (keycode == K_PGDW && fdf->data.curr_proj->id == ISO)
		fdf->data.z_scaling += 0.5;
	else if (keycode == K_ESC)
	{
		delete_mlx(fdf);
		exit(0);
	}
	key_handler_do_rotation(keycode, fdf);
	key_handler_change_proj(keycode, fdf);
}

/* Every time a key is pressed, key_handler() is called.
 * It re-adjust the origin position to get the map centered by computing the
 * center BEFORE any key is pressed, and the center AFTER any key is pressed.
 * By doing so, we can adjust the origin position to match the difference of the
 * two center.*/

int	key_handler(int keycode, t_mlx *fdf)
{
	t_vec2d	curr_center;
	t_vec2d	future_center;

	curr_center = get_center(&fdf->data, fdf->data.tile_width);
	fdf->data.curr_proj->last_alpha = fdf->data.curr_proj->alpha;
	fdf->data.curr_proj->last_beta = fdf->data.curr_proj->beta;
	fdf->data.curr_proj->last_gamma = fdf->data.curr_proj->gamma;
	key_handler_do(keycode, fdf);
	if (fdf->data.tile_width < 1)
		fdf->data.tile_width = 1;
	if (fdf->data.z_scaling < 1)
		fdf->data.z_scaling = 1;
	wipe_render_scene(fdf);
	future_center = get_center(&fdf->data, fdf->data.tile_width);
	fdf->data.org.x -= future_center.x - curr_center.x;
	fdf->data.org.y -= future_center.y - curr_center.y;
	render(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
	return (keycode);
}

/* This function is called during the loading phase, it returns a message and
 * free the program memory before exiting via the main() function. */

int	raise_errors(t_mlx *fdf, int errcode)
{
	if (errcode == ERR_MALLOC)
		ft_printf(FATAL STR_ERR_MALLOC);
	else if (errcode == ERR_ARGC)
		ft_printf(WARNING STR_ERR_ARGC);
	else if (errcode == ERR_MAP)
		ft_printf(FATAL STR_ERR_MAP);
	if (fdf)
		delete_mlx(fdf);
	return (errcode);
}
