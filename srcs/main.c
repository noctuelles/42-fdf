/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/12 23:51:06 by plouvel          ###   ########.fr       */
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

void	apply_isometric(t_mlx *fdf)
{
	t_vec3d	*vec3d;
	size_t	tile_height;
	int		x;
	int		y;
	t_vec2d	proj;

	tile_height = fdf->data.tile_width / 2;
	y = 0;
	while (y < fdf->data.nbr_lines)
	{
		x = 0;
		while (x < fdf->data.elems_line)
		{
			proj.x = (x - y) * (fdf->data.tile_width / 2);
			proj.y = (-fdf->data.vertices[y][x] * (tile_height / 2)) +
											(x + y) * (tile_height / 2);
			put_pixel(fdf, fdf->data.org.x + proj.x, fdf->data.org.y + proj.y, 0xffff0000);
			x++;
		}
		y++;
	}
}

t_vec2d	transform_isometric(size_t tile_width, t_vec3d vec3d)
{
	t_vec2d	proj;
	size_t	tile_height;

	tile_height = tile_width / 2;
	proj.x = (vec3d.x - vec3d.y) * (tile_width / 2);
	proj.y = -vec3d.z * (tile_height / 2) + (vec3d.x + vec3d.y) * (tile_height / 2);
	proj.x += data->org.x;
	proj.y += data->org.y;
	return (proj);
}

int		is_edges_outside(t_vec2d edges[4])
{
	if (edges[0].y > HEIGHT || edges[0].y < 0)
		return (1);
	else if (edges[1].x <= 300)
		return (1);
	else if (edges[2].y > HEIGHT)
		return (1);
	else if (edges[3].x > WIDTH)
		return (1);
	else
		return (0);
}

size_t	compute_tile_width(t_mlx_data *data)
{
	t_vec2d	edges[4];
	size_t	tile_width;

	tile_width = 4;
	while (1)
	{
		edges[0] = transform_isometric(tile_width, data->edges[0]);
		edges[1] = transform_isometric(tile_width, data->edges[1]);
		edges[2] = transform_isometric(tile_width, data->edges[2]);
		edges[3] = transform_isometric(tile_width, data->edges[3]);
		if (is_edges_outside(edges))
			return (tile_width - 1);
		tile_width++;
	}
	return (tile_width);
}
/*
t_org_data	find_best(t_mlx_data *data)
{
	t_org_data	org_data[40];
	size_t		i;
	t_vec2d		org;

	org.x = data->org.x;
	org.y = data->org.y;
	i = 0;
	while (i < 40)
	{
		org_data[i].tile_width = compute_tile_width(data);
		org_data[i].org.x = data->org.x;
		org_data[
	}
}*/

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
	t_vec2d	vec = {.x = 300, .y = 0};
	t_vec2d	vece = {.x = WIDTH, .y = HEIGHT};
	t_vec2d	vec0 = {.x = 300, .y = HEIGHT};
	fdf->data.vertices = parse_map("mars.fdf", &fdf->data);
	draw_line(fdf, vec, vec0, 0xffffffff);
	//draw_line(fdf, vec, vece, 0xffffffff);
	fdf->data.tile_width = compute_tile_width(&fdf->data);
	apply_isometric(fdf);
	// put_pixel(fdf, 350, 50, 0xffff0000);		: ceci est l'origine
	/*fdf->data.vertices = parse_map("42.fdf", &fdf->data);
	fdf->data.tile_width = 80;
	apply_isometric(&fdf->data);
	render_isometric(fdf);*/
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
