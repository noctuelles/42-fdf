/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:28:59 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/28 16:38:51 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

/* key_handler_change_proj() is about the keys that change the current proj-
 * -jection. */

static inline void	key_handler_change_proj(int keycode, t_mlx *fdf)
{
	if (keycode == K_P && fdf->data.curr_proj->id == ISO)
		set_projection(&fdf->data, ORTHO);
	else if (keycode == K_P && fdf->data.curr_proj->id == ORTHO)
		set_projection(&fdf->data, ISO);
}

/*
static inline void key_handler_reset(int keycode, t_mlx *fdf)
{
	if (keycode == K_O)
	{
		fdf->data.curr_proj->alpha = 0;
		fdf->data.curr_proj->beta = 0;
		fdf->data.curr_proj->gamma = 0;
		fdf->data.org = fdf->data.first_org;
	}
}
*/

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
	if (fdf->data.tile_width < 1)
		fdf->data.tile_width = 1;
	else if (fdf->data.z_scaling < 1)
		fdf->data.z_scaling = 1;
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
	key_handler_do_rotation(keycode, fdf);
	key_handler_change_proj(keycode, fdf);
	future_center = get_center(&fdf->data, fdf->data.tile_width);
	fdf->data.org.x -= future_center.x - curr_center.x;
	fdf->data.org.y -= future_center.y - curr_center.y;
	wipe_render_scene(fdf);
	render(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
	return (keycode);
}
