/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/19 19:50:13 by plouvel          ###   ########.fr       */
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
	center = transform_isometric(tile_width, org_hud, vec, data);
	return (center);
}

int	is_edges_negative(t_vec2d map_edges[4])
{
	size_t	i;

	i = 1;
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
		edges[0] = transform_isometric(tile_width, data->org, map_edges[0], data);
		edges[1] = transform_isometric(tile_width, data->org, map_edges[1], data);
		edges[2] = transform_isometric(tile_width, data->org, map_edges[2], data);
		edges[3] = transform_isometric(tile_width, data->org, map_edges[3], data);
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

void write_bit(int c)
{
	int i;

	i = 31;
	while (i >= 0)
	{
		if (c & (1UL << i))
			write(1, "1", 1);
		else
			write(1, "0", 1);
		i--;
	}
	write(1, "\n", 1);
}
int	main(int argc, char **argv)
{
	t_mlx	*fdf;

	fdf = NULL;
	if (argc != 2)
		return (raise_errors(fdf, ERR_ARGC));
	fdf = new_mlx(WIDTH, HEIGHT, "Wireframe (FdF) viewer");
	if (!fdf)
		return (raise_errors(fdf, ERR_MALLOC));
	fdf->data.vertices = parse_map(argv[1], &fdf->data);
	if (!fdf->data.vertices)
		return (raise_errors(fdf, ERR_MAP));
	t_vec2d	screen_rg = {.x = 0, .y = 0};
	//draw_line(fdf, vec, vece, 0xffffffff);
	draw_hud_bg(fdf);
	draw_keys(fdf);
	t_vec2d org_hud;
	org_hud.x = 200;
	org_hud.y = 0;
	//fdf->data.tile_width = compute_tile_width(&fdf->data, fdf->data.edges, org_hud);
	fdf->data.tile_width = 1;
	fdf->data.org.x = 500;
	fdf->data.org.y = 500;
	//printf("%ld\n", fdf->data.tile_width);
	apply_isometric(fdf);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
	mlx_hook(fdf->wnd, 2, 1L<<0, &key_handler, fdf);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
