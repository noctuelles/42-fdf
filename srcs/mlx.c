/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 17:07:30 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/31 19:45:58 by plouvel          ###   ########.fr       */
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
	mlx->data.width = width;
	mlx->data.height = height;
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
	return (mlx);
}

void	put_pixel(t_mlx *mlx, int x, int y, uint32_t color)
{
	char	*pixel_addr;

	pixel_addr = mlx->addr + (x * (mlx->bpp / 8) + y * mlx->line_len);
	*(uint32_t *)pixel_addr = color;
}

uint32_t	get_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	delete_mlx(t_mlx *mlx)
{
	free(mlx);
}
