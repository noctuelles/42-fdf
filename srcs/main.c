/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/17 22:28:02 by plouvel          ###   ########.fr       */
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

size_t	get_text_pixel_size(char *txt)
{
	return (strlen(txt) * 6 - 1);
}



/* Instead of using get_next_line to count line, i use a dedicated fonction */

void	apply_isometric(t_mlx *fdf)
{
	t_vec3d	vec3d;
	t_vec2d	vec2d[3];
	size_t	tile_height;
	int		x;
	int		y;
	t_vec2d	proj;

	tile_height = fdf->data.tile_width / 2;
	fdf->data.drawing = 1;
	y = 0;
	while (y < fdf->data.nbr_lines)
	{
		x = 0;
		while (x < fdf->data.elems_line)
		{
			vec3d.x = x;
			vec3d.y = y;
			vec3d.z = fdf->data.vertices[y][x];
			if (vec3d.z != 0)
				vec3d.z += fdf->data.z_scaling;
			vec2d[0] = transform_isometric(fdf->data.tile_width, fdf->data.org, vec3d);
			//printf("Point no %d is at X : %d and Y : %d\n", x, vec2d[0].x, vec2d[0].y);
			//put_pixel(fdf, vec2d[0].x, vec2d[0].y, 0xffffffff);
			if (x < fdf->data.elems_line - 1)
			{
				vec3d.x = x + 1;
				vec3d.y = y;
				vec3d.z = fdf->data.vertices[y][x + 1];
				if (vec3d.z != 0)
					vec3d.z += fdf->data.z_scaling;
				vec2d[1] = transform_isometric(fdf->data.tile_width, fdf->data.org, vec3d);
				//put_pixel(fdf, vec2d[1].x, vec2d[1].y, 0xffff0000);
				draw_line(fdf, vec2d[1], vec2d[0], 0xffffffff);
			}
		
			if (y > 0)
			{
				vec3d.x = x;
				vec3d.y = y - 1;
				vec3d.z = fdf->data.vertices[y - 1][x];
				if (vec3d.z != 0)
					vec3d.z += fdf->data.z_scaling;
				vec2d[2] = transform_isometric(fdf->data.tile_width, fdf->data.org, vec3d);
				draw_line(fdf, vec2d[0], vec2d[2], 0xffffffff);
			}
			x++;
		}
		y++;
	}
}

int		is_edges_outside(t_vec2d edges[4])
{
	if (edges[0].y > HEIGHT || edges[0].y < 0)
		return (1);
	else if (edges[1].x <= 200)
		return (1);
	else if (edges[2].y > HEIGHT)
		return (1);
	else if (edges[3].x > WIDTH)
		return (1);
	else
		return (0);
}

/*
 *	get_center_iso() return the center of the isometric map, according to the
 *	render origin (so called org_hud)
 *
 */

t_vec2d	get_center_iso(t_mlx_data *data, size_t tile_width, t_vec2d org_hud)
{
	t_vec2d	center;
	t_vec3d	vec;

	vec.x = roundf(data->elems_line / 2);
	vec.y = roundf(data->nbr_lines / 2);
	vec.z = 0;
	center = transform_isometric(tile_width, org_hud, vec);
	return (center);
}

int	is_edges_negative(t_vec2d map_edges[4])
{
	size_t	i;

	i = 0;
	while (i < 4)
	{
		if (map_edges[i].x < 0 || map_edges[i].y < 0)
			return (1);
		i++;
	}
	return (0);
}

size_t	compute_tile_width(t_mlx_data *data, t_vec3d map_edges[4], t_vec2d org_hud)
{
	t_vec2d	edges[4];
	t_vec2d	old_org;
	t_vec2d	iso_center;
	size_t	tile_width;

	tile_width = 4;
	while (1)
	{
		iso_center = get_center_iso(data, tile_width, org_hud); 
		data->org.x = 200 + (950 - iso_center.x);
		data->org.y = 500 - iso_center.y;
		edges[0] = transform_isometric(tile_width, data->org, map_edges[0]);
		edges[1] = transform_isometric(tile_width, data->org, map_edges[1]);
		edges[2] = transform_isometric(tile_width, data->org, map_edges[2]);
		edges[3] = transform_isometric(tile_width, data->org, map_edges[3]);
		if (is_edges_negative(edges))
			return (tile_width);
		if (is_edges_outside(edges))
		{
			data->org.x = old_org.x;
			data->org.y = old_org.y;
			return (tile_width - 1);
		}
		old_org.x = data->org.x;
		old_org.y = data->org.y;
		tile_width++;
	}
	return (tile_width);
}

void wipe(t_mlx *fdf)
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

int	zoom(int keycode, t_mlx *fdf)
{
	if (keycode == 0x3d)
		fdf->data.tile_width += 4;
	else if (keycode == 0x2d)
		fdf->data.tile_width -= 4;
	else if (keycode == 0xff52)
		fdf->data.org.y -= 4;
	else if (keycode == 0xff54)
		fdf->data.org.y += 4;
	else if (keycode == 0xff51)
		fdf->data.org.x -= 4;
	else if (keycode == 0xff53)
		fdf->data.org.x += 4;
	else if (keycode == 0xff55)
		fdf->data.z_scaling--;
	else if (keycode == 0xff56)
		fdf->data.z_scaling++;
	wipe(fdf);
	apply_isometric(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
}

int	main(int argc, char **argv)
{
	t_mlx	*fdf;

	fdf = new_mlx(WIDTH, HEIGHT, "Wireframe (FdF) viewer");
	if (!fdf)
		return (1);
	t_vec2d	screen_rg = {.x = 0, .y = 0};
	fdf->data.vertices = parse_map(argv[1], &fdf->data);
	//draw_line(fdf, vec, vece, 0xffffffff);
	draw_hud_bg(fdf);
	draw_keys(fdf);
	t_vec2d org_hud;
	org_hud.x = 200;
	org_hud.y = 0;
	fdf->data.tile_width = compute_tile_width(&fdf->data, fdf->data.edges, org_hud);
	//printf("%ld\n", fdf->data.tile_width);
	apply_isometric(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
	mlx_hook(fdf->wnd, 2, 1L<<0, zoom, fdf);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
