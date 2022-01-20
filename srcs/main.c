/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/20 19:50:04 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>



/*
 *	get_center_iso() return the center of the isometric map, according to the
 *	render origin (so called org_hud)
 *
 */

void write_bit(int c)
{
	int i;

	i = 31;
	while (i >= 0)
	{
		if (c & (1UL << i))
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i--;
	}
	write(1, "\n", 1);
}

uint32_t	*get_color_gradient(uint32_t colors[2], t_vec2d pts[2])
{
	float		red_inc;
	float		green_inc;
	float		blue_inc;
	int			nbr_px;
	size_t		i;
	uint32_t	*gradient;

	nbr_px = MAX(ABS(pts[1].y - pts[0].y), ABS(pts[1].x - pts[0].x));
	printf("nbr px %d\n", nbr_px);
	gradient = (uint32_t *) malloc(nbr_px * sizeof(uint32_t));
	if (!gradient)
		return (NULL);
	i = 0;

	int		val_red = R(colors[1]) - R(colors[0]);
	int		val_green = G(colors[1]) - G(colors[0]);
	int		val_blue = B(colors[1]) - B(colors[0]);
	printf ("%d\n", val_green);
	red_inc =  (float) val_red / nbr_px;
	green_inc = (float) val_green / nbr_px;
	blue_inc = (float) val_blue / nbr_px;
	printf("red_inc : %f\n"
			"green_inc : %f\n"
			"blue inc : %f\n", red_inc, green_inc, blue_inc);
	while (i < nbr_px)
	{
		gradient[i] = NEW_COLOR(R(colors[0]) + (int)roundf(((i + 1) * red_inc)),
								G(colors[0]) + (int)roundf(((i + 1) * green_inc)),
								B(colors[0]) + (int)roundf(((i + 1) * blue_inc)));
		i++;
	}
	return (gradient);
}

# define WH 0xffffffff
# define RD 0xffb57cf0

int	main(int argc, char **argv)
{
	t_mlx	*fdf;
	uint32_t	colors[2];
	uint32_t	*gradient;
	t_vec2d		pts[2];

	colors[0] = WH;
	colors[1] = RD;
	pts[0].x = 400;
	pts[0].y = 400;
	pts[1].x = 1200;
	pts[1].y = 400;
	gradient = get_color_gradient(colors, pts);

	fdf = NULL;
	if (argc != 2)
		return (raise_errors(fdf, ERR_ARGC));
	fdf = new_mlx(WIDTH, HEIGHT, "Wireframe (FdF) viewer");
	if (!fdf)
		return (raise_errors(fdf, ERR_MALLOC));
	fdf->data.vertices = parse_map(argv[1], &fdf->data);
	if (!fdf->data.vertices)
		return (raise_errors(fdf, ERR_MAP));
	draw_hud_bg(fdf);
	draw_keys(fdf);
	fdf->data.tile_width = setup_map(&fdf->data, fdf->data.edges,
															new_vec2d(200, 0));
	//apply_isometric(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
	mlx_key_hook(fdf->wnd, &key_handler, fdf);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
