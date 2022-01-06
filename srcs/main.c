/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/06 15:10:47 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

void	draw_rect(t_mlx *mlx, t_vec2d pos, t_vec2d v, uint32_t color)
{
	t_vec2d	org;

	org = pos;
	pos.y += v.y;
	draw_line(mlx, org, pos, color); 
	pos.x++;
	pos.y--;
	org = pos;
	if (v.x - 2 > 0)
	{
		ft_printf("not too short");
		pos.x += v.x - 2;
		draw_line(mlx, org, pos, color); 
		pos.x--;
		org = pos;
	}
	pos.y -= v.y - 1;
	draw_line(mlx, org, pos, color); 
	/*
	org = pos;
	if (v.x - 2 > 0)
	{
		pos.x -= v.x - 2;
		draw_line(mlx, org, pos, color); 
	}*/
}

int	main(int argc, char **argv)
{
	t_mlx	*fdf;

	fdf = new_mlx(WIDTH, HEIGHT, "fdf");
	if (!fdf)
		return (1);
	/*while (lst)
	{
		t_vec3d vec = *(t_vec3d *)lst->content;
		int old_x = vec.x;
		int old_y = vec.y;
		int old_z = vec.z;
		const int tile_width = 40;
		const int tile_height = tile_width / 2;
		vec.x = (old_x - old_y) * (tile_width / 2);
		vec.y = -(old_z * (tile_height / 2)) + (old_x + old_y) * (tile_height / 2);
		//vec.x = vec.x + 400;
		//vec.y = -vec.y + 400;
		put_pixel(fdf, vec.x + 400, vec.y + 400, 0xffff0000);
		lst = lst->next;
	}*/
	t_vec2d org = {.x = 200, .y = 200};
	t_vec2d v = {.x = 2, .y = 2};
	draw_rect(fdf, org, v, 0xffcccccc);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
