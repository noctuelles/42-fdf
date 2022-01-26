/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/26 22:46:23 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

static int	setup_window(t_mlx *fdf)
{
	fdf->data.gradient = get_color_gradient(START_COLOR, END_COLOR,
			ft_abs(fdf->data.min_z) + ft_abs(fdf->data.max_z));
	if (!fdf->data.gradient)
		return (ERR_MALLOC);
	draw_hud_bg(fdf);
	draw_keys(fdf);
	fdf->data.transform = &transform_isometric;
	fdf->data.tile_width = setup_map(&fdf->data, fdf->data.edges,
			new_vec2d(200, 0));
	render(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
	return (0);
}

static int	destroy(t_mlx *fdf)
{
	delete_mlx(fdf);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	*fdf;

	fdf = NULL;
	if (argc != 2)
		return (raise_errors(fdf, ERR_ARGC));
	fdf = new_mlx(WIDTH, HEIGHT, "Wireframe (FdF) viewer");
	if (!fdf)
		return (raise_errors(fdf, ERR_MALLOC));
	fdf->data.vertices = parse_map(argv[1], &fdf->data);
	if (!fdf->data.vertices)
		return (raise_errors(fdf, ERR_MAP));
	if (setup_window(fdf) != 0)
		return (raise_errors(fdf, ERR_MALLOC));
	mlx_hook(fdf->wnd, 2, 1L << 0, &key_handler, fdf);
	mlx_hook(fdf->wnd, 17, 1L << 0, &destroy, fdf);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
