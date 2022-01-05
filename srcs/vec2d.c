/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 19:24:31 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/31 19:45:11 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_vec2d(t_vec2d *vec, double angle)
{
}

void	draw_vec2d(t_mlx *mlx, t_vec2d org, t_vec2d vec, uint32_t color)
{
	vec.x += org.x;
	vec.y += org.y;
	draw_line(mlx, org, vec, color);
}
