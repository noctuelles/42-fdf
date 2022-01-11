/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/11 19:07:46 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

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

/* Instead of using get_next_line to count line, i use a dedicated fonction */



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
	fdf->data.vertices = parse_map("mars.fdf", &fdf->data);
	/*fdf->data.vertices = parse_map("42.fdf", &fdf->data);
	fdf->data.tile_width = 80;
	apply_isometric(&fdf->data);
	render_isometric(fdf);*/
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}