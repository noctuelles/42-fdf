/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:07:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/19 13:42:45 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <stdlib.h>

t_mlx	*new_mlx(uint16_t width, uint16_t height, const char *title)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) malloc(sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	ft_memset(&mlx->data, 0, sizeof(t_mlx_data));
	mlx->inst = mlx_init();
	if (!mlx->inst)
		return (NULL);
	mlx->wnd = mlx_new_window(mlx->inst, width, height, (char *)title);
	if (!mlx->wnd)
		return (NULL);
	mlx->img = mlx_new_image(mlx->inst, width, height);
	if (!mlx->img)
		return (NULL);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp,
												&mlx->line_len, &mlx->endian);
	if (!mlx->addr)
		return (NULL);
	mlx->data.org.x = 700;
	mlx->data.org.y = 250;
	mlx->data.z_scaling = 1;
	mlx->data.tile_width = 4;
	return (mlx);
}

/*static inline void	put_pixel(t_mlx *mlx, int x, int y, uint32_t color)
{
	char	*pixel_addr;
	int		pixel_x;
	int		pixel_y;

	pixel_addr = mlx->addr + (x * (mlx->bpp / 8) + y * mlx->line_len);
	*(uint32_t *)pixel_addr = color;
}*/

uint32_t	get_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	wipe_render_scene(t_mlx *fdf)
{
	int	x = 200;
	int y = 0;

	while (y < HEIGHT)
	{
		x = 200;
		while (x < WIDTH)
		{
			put_pixel(fdf, x, y, 0xff000000);
			x++;
		}
		y++;
	}
}

void	delete_mlx(t_mlx *mlx)
{
	if (mlx->wnd)
		mlx_destroy_window(mlx->inst, mlx->wnd);
	if (mlx->img)
		mlx_destroy_image(mlx->inst, mlx->img);
	if (mlx->inst)
	{
		mlx_destroy_display(mlx->inst);
		free(mlx->inst);
	}
	if (mlx->data.vertices)
		free_vertices(mlx->data.vertices);
	free(mlx);
}
