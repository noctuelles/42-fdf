/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/21 15:34:27 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

static void	setup_window(t_mlx *fdf)
{
	draw_hud_bg(fdf);
	draw_keys(fdf);
	fdf->data.tile_width = setup_map(&fdf->data, fdf->data.edges,
			new_vec2d(200, 0));
	apply_isometric(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
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
	setup_window(fdf);
	mlx_hook(fdf->wnd, 2, 1L << 0, &key_handler, fdf);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
