/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:25:31 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/23 12:59:21 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*static void	draw_hor_line(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
																uint32_t color)
{
	int	tmp;

	if (p2.x < p1.x)
	{
		tmp = p2.x;
		p2.x = p1.x;
		p1.x = tmp;
	}
	while (p1.x < p2.x)
	{
		put_pixel(mlx, p1.x, p1.y, color);
		p1.x++;
	}
}

static void	draw_ver_line(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
																uint32_t color)
{
	int	tmp;

	if (p2.y < p1.y)
	{
		tmp = p2.y;
		p2.y = p1.y;
		p1.y = tmp;
	}
	while (p1.y < p2.y)
	{
		put_pixel(mlx, p1.x, p1.y, color);
		p1.y++;
	}
}*/

static void	draw_line_low(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
																uint32_t color)
{
	t_vec2d		delta;
	int			d;
	int			sign;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	sign = 1;
	if (delta.y < 0)
	{
		sign = -1;
		delta.y = -delta.y;
	}
	d = 2 * delta.y - delta.x;
	while (p1.x < p2.x)
	{
		put_pixel(mlx, p1.x++, p1.y, color);
		if (d < 0)
			d = d + 2 * delta.y;
		else
		{
			p1.y += sign;
			d = d + 2 * (delta.y - delta.x);
		}
	}
}

static void	draw_line_high(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
																uint32_t color)
{
	t_vec2d	delta;
	int		d;
	int		sign;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	sign = 1;
	if (delta.x < 0)
	{
		sign = -1;
		delta.x = -delta.x;
	}
	d = 2 * delta.x - delta.y;
	while (p1.y < p2.y)
	{
		put_pixel(mlx, p1.x, p1.y++, color);
		if (d < 0)
			d = d + 2 * delta.x;
		else
		{
			p1.x += sign;
			d = d + (2 * (delta.x - delta.y));
		}
	}
}

void	draw_line(t_mlx *mlx, t_vec2d p1, t_vec2d p2, uint32_t color)
{
	if (ft_abs(p2.y - p1.y) < ft_abs(p2.x - p1.x))
	{
		if (p1.x > p2.x)
			draw_line_low(mlx, p2, p1, color);
		else
			draw_line_low(mlx, p1, p2, color);
	}
	else
	{
		if (p1.y > p2.y)
			draw_line_high(mlx, p2, p1, color);
		else
			draw_line_high(mlx, p1, p2, color);
	}
}
