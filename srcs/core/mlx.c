/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:07:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/20 19:26:31 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>
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
	mlx->data.z_scaling = 7;
	mlx->data.cos_theta = cos(ANGLE_ISO);
	mlx->data.sin_theta = sin(ANGLE_ISO);
	return (mlx);
}

uint32_t	get_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	wipe_render_scene(t_mlx *fdf)
{
	int x = 0;
	int y = 0;
	char	*pixel_addr;

	while (y < HEIGHT)
	{
		x = 200;
		while (x < WIDTH)
		{
			pixel_addr = fdf->addr + (x * (fdf->bpp / 8) + y * fdf->line_len);
			*(uint32_t *)pixel_addr = 0xff000000;
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
