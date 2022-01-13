/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/13 19:20:32 by plouvel          ###   ########.fr       */
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

t_key	draw_key(t_mlx *mlx, t_vec2d pos, char *txt_key)
{
	t_vec2d outside_rect;
	t_vec2d	inner_rect;
	t_vec2d	inner_rect_pos;
	t_key	key;
	size_t	txt_size;

	outside_rect.x = 40;
	outside_rect.y = 40;
	inner_rect.x = 26;
	inner_rect.y = 26;
	inner_rect_pos.x = pos.x + 7;
	inner_rect_pos.y = pos.y + 7;
	draw_full_rect(mlx, outside_rect, pos, 0xffc0c0c0);
	draw_full_rect(mlx, inner_rect, inner_rect_pos, 0xff000000);
	txt_size = get_text_pixel_size(txt_key);
	key.y = inner_rect_pos.y + 13;
	key.x = (26 - txt_size) + (txt_size / 2); 
	key.txt_key = txt_key;
	return (key);
}

void	draw_key_txt(t_mlx *mlx, t_key keys[13])
{
	size_t	i;

	i = 0;
	while (i < 13)
	{
		mlx_string_put(mlx->inst, mlx->wnd, keys[i].x, keys[i].y, 0xffffffff, keys[i].txt_key);
		i++;
	}
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

size_t	compute_tile_width(t_vec3d map_edges[4], t_vec2d org)
{
	t_vec2d	edges[4];
	size_t	tile_width;

	tile_width = 4;
	while (1)
	{
		edges[0] = transform_isometric(tile_width, org, map_edges[0]);
		edges[1] = transform_isometric(tile_width, org, map_edges[1]);
		edges[2] = transform_isometric(tile_width, org, map_edges[2]);
		edges[3] = transform_isometric(tile_width, org, map_edges[3]);
		if (is_edges_outside(edges))
			return (tile_width - 1);
		tile_width++;
	}
	return (tile_width);
}

t_org_data	find_best_org(t_vec3d edges[4], t_vec2d initial_org)
{
	t_org_data	org_data[50];
	t_org_data	best;
	size_t		i;
	t_vec2d		org;

	org.x = initial_org.x;
	org.y = initial_org.y;
	i = 0;
	while (i < 50)
	{
		org_data[i].tile_width = compute_tile_width(edges, org);
		org_data[i].org.x = org.x;
		org_data[i].org.y = org.y;
		org.x += 25;
		i++;
	}
	i = 0;
	best.tile_width = 4;
	while (i < 50)
	{
		if (org_data[i].tile_width > best.tile_width)
		{
			best.tile_width = org_data[i].tile_width;
			best.org.x = org_data[i].org.x;
			best.org.y = org_data[i].org.y;
		}
		i++;
	}
	return (best);
}

int	main(int argc, char **argv)
{
	t_mlx	*fdf;

	fdf = new_mlx(WIDTH, HEIGHT, "Wireframe (FdF) viewer");
	if (!fdf)
		return (1);
	t_vec2d	screen_rg = {.x = 0, .y = 0};
	fdf->data.vertices = parse_map("mars.fdf", &fdf->data);
	//draw_line(fdf, vec, vece, 0xffffffff);
	t_org_data	best = find_best_org(fdf->data.edges, fdf->data.org);
	fdf->data.tile_width = best.tile_width;
	fdf->data.org.x = best.org.x;
	fdf->data.org.y = best.org.y;
	draw_hud_bg(fdf);
	apply_isometric(fdf);
	/*t_vec2d pos;
	pos.x = 80;
	pos.y = 100;
	draw_key(fdf, pos, "W");
	pos.y += 50;
	pos.x -= 50;
	draw_key(fdf, pos, "A");
	pos.y += 100;
	draw_key(fdf, pos, "+");
	pos.y += 100;
	draw_key(fdf, pos, "PU");
	pos.y -= 200;
	pos.x += 50;
	draw_key(fdf, pos, "S");
	pos.x += 50;
	draw_key(fdf, pos, "D");
	pos.y += 100;
	draw_key(fdf, pos, "-");
	pos.y += 100;
	draw_key(fdf, pos, "PD");*/
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	draw_hud_static_text(fdf);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
