/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_gradient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:36:22 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/24 15:39:08 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

static void	draw_line_low_g(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
																uint32_t *color)
{
	t_vec2d		delta;
	int			d;
	int			sign;
	int			i;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	sign = 1;
	i = 0;
	if (delta.y < 0)
	{
		sign = -1;
		delta.y = -delta.y;
	}
	d = 2 * delta.y - delta.x;
	while (p1.x < p2.x)
	{
		put_pixel(mlx, p1.x++, p1.y, color[i]);
		if (d < 0)
			d = d + 2 * delta.y;
		else
		{
			p1.y += sign;
			d = d + 2 * (delta.y - delta.x);
		}
		i++;
	}
}

static void	draw_line_high_g(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
																uint32_t *color)
{
	t_vec2d	delta;
	int		d;
	int		sign;
	int		i;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	sign = 1;
	i = 0;
	if (delta.x < 0)
	{
		sign = -1;
		delta.x = -delta.x;
	}
	d = 2 * delta.x - delta.y;
	while (p1.y < p2.y)
	{
		put_pixel(mlx, p1.x, p1.y++, color[i]);
		if (d < 0)
			d = d + 2 * delta.x;
		else
		{
			p1.x += sign;
			d = d + (2 * (delta.x - delta.y));
		}
		i++;
	}
}

static inline void	gen_gradient_n_draw_low(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
															unsigned int len)
{
	uint32_t	*gradient;

	gradient = get_color_gradient(p1.color, p2.color, len);
	if (!gradient)
	{
		exit(ERR_MALLOC);
		delete_mlx(mlx);
	}
	draw_line_low_g(mlx, p1, p2, gradient);
	free(gradient);
}

static inline void	gen_gradient_n_draw_high(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
															unsigned int len)
{
	uint32_t	*gradient;

	gradient = get_color_gradient(p1.color, p2.color, len);
	if (!gradient)
	{
		exit(ERR_MALLOC);
		delete_mlx(mlx);
	}
	draw_line_high_g(mlx, p1, p2, gradient);
	free(gradient);
}

void	draw_line_gradient(t_mlx *mlx, t_vec2d p1, t_vec2d p2)
{
	t_vec2d		abs_diff;

	abs_diff.x = ft_abs(p2.x - p1.x);
	abs_diff.y = ft_abs(p2.y - p1.y);
	if (abs_diff.y < abs_diff.x)
	{
		if (p1.x > p2.x)
			gen_gradient_n_draw_low(mlx, p2, p1, abs_diff.x);
		else
			gen_gradient_n_draw_low(mlx, p1, p2, abs_diff.x);
	}
	else
	{
		if (p1.y > p2.y)
			gen_gradient_n_draw_high(mlx, p2, p1, abs_diff.y);
		else
			gen_gradient_n_draw_high(mlx, p1, p2, abs_diff.y);
	}
}
