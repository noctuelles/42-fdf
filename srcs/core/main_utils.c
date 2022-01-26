/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:49:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/26 22:54:37 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

static void	key_handler_change_proj(int keycode, t_mlx *fdf)
{
	if (keycode == K_P && fdf->data.projection_type == PROJ_ISO)
	{
		fdf->data.saved_gamma = fdf->data.gamma;
		fdf->data.org.x -= 300;
		fdf->data.projection_type = PROJ_ORTHO;
		fdf->data.transform = &transform_ortho;
	}
	else if (keycode == K_P && fdf->data.projection_type == PROJ_ORTHO)
	{
		fdf->data.gamma = fdf->data.saved_gamma;
		fdf->data.org.x += 300;
		fdf->data.projection_type = PROJ_ISO;
		fdf->data.transform = &transform_isometric;
	}
}

static void	key_handler_do_rotation(int keycode, t_mlx *fdf)
{
	if (keycode == K_UP)
		fdf->data.alpha += 0.05;
	else if (keycode == K_DOWN)
		fdf->data.alpha -= 0.05;
	else if (keycode == K_RIGHT)
		fdf->data.beta += 0.05;
	else if (keycode == K_LEFT)
		fdf->data.beta -= 0.05;
	if (keycode == K_E)
		fdf->data.gamma += 0.05;
	else if (keycode == K_R)
		fdf->data.gamma -= 0.05;
}

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
	else if (keycode == K_PGUP && fdf->data.projection_type == PROJ_ISO)
		fdf->data.z_scaling -= 0.5;
	else if (keycode == K_PGDW && fdf->data.projection_type == PROJ_ISO)
		fdf->data.z_scaling += 0.5;
	else if (keycode == K_ESC)
	{
		delete_mlx(fdf);
		exit(0);
	}
	key_handler_do_rotation(keycode, fdf);
	key_handler_change_proj(keycode, fdf);
}

int	key_handler(int keycode, t_mlx *fdf)
{
	t_vec2d	curr_center;
	t_vec2d	future_center;
	t_vec2d	org_hud;

	set_vec2d(&org_hud, 200, 0);
	curr_center = get_center_iso(&fdf->data, fdf->data.tile_width, org_hud);
	fdf->data.last_alpha = fdf->data.alpha;
	fdf->data.last_beta = fdf->data.beta;
	fdf->data.last_gamma = fdf->data.gamma;
	key_handler_do(keycode, fdf);
	if (fdf->data.tile_width < 1)
		fdf->data.tile_width = 1;
	if (fdf->data.z_scaling < 1)
		fdf->data.z_scaling = 1;
	wipe_render_scene(fdf);
	future_center = get_center_iso(&fdf->data, fdf->data.tile_width, org_hud);
	fdf->data.org.x -= future_center.x - curr_center.x;
	fdf->data.org.y -= future_center.y - curr_center.y;
	render(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
	return (keycode);
}

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
