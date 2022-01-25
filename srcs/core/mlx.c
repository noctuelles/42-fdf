/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:07:30 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/25 14:34:17 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

static void	setup_angle(t_mlx_data *data)
{
	data->cos_theta = cos(ANGLE_ISO);
	data->sin_theta = sin(ANGLE_ISO);
	data->sin_alpha = sin(data->alpha);
	data->cos_alpha = cos(data->alpha);
	data->sin_beta = sin(data->beta);
	data->cos_beta = cos(data->beta);
	data->sin_gamma = sin(data->gamma);
	data->cos_gamma = cos(data->gamma);
}

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
	setup_angle(&mlx->data);
	return (mlx);
}

void	wipe_render_scene(t_mlx *fdf)
{
	int		x;
	int		y;
	char	*pixel_addr;

	y = 0;
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
	mlx_loop_end(mlx);
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
	free(mlx->data.gradient);
	free(mlx);
}
