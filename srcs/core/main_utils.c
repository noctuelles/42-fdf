/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:49:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/19 23:05:46 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	else if (keycode == K_PGUP)
	{
		fdf->data.z_scaling -= 0.5;
	}
	else if (keycode == K_PGDW)
		fdf->data.z_scaling += 0.5;
	else if (keycode == K_ESC)
	{
		delete_mlx(fdf);
		exit(0);
	}
	else if (keycode == K_RIGHT)
		fdf->data.alpha += 0.05;
	else if (keycode == K_LEFT)
		fdf->data.alpha -= 0.05;
	else if (keycode == K_UP)
		fdf->data.beta += 0.05;
	else if (keycode == K_DOWN)
		fdf->data.beta -= 0.05;
	else if (keycode == K_ALTGR)
		fdf->data.gamma += 0.05;
	else if (keycode == K_CRTL)
		fdf->data.gamma -= 0.05;
}

int	key_handler(int keycode, t_mlx *fdf)
{
	key_handler_do(keycode, fdf);
	wipe_render_scene(fdf);
	apply_isometric(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
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
