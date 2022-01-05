/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 00:06:36 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/05 15:15:41 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

int	ft_abs(int i)
{
	if (i)
		return (i);
	return (-i);
}
void	iso(t_vec2d *vec)
{
	int	old_x;
	int	old_y;

	old_x = vec->x;
	old_y = vec->y;
	vec->x = old_x - old_y;
	vec->y = (old_x + old_y) / 2;
}
/*
size_t	get_file_infos(int fd, t_mlx_data *data)
{
	ssize_t	rded;
	char	*nw_addr;
	char	buffer[1024];

	rded = read(fd, buffer, 1024);
	while (rded)
	{
		nw_addr = ft_strchr(buffer, '\n');
		if (nw_addr)
		{
			data->nbr_line++;
			buffer = nw_addr + 1;
		}
		else
			rded = read(fd, buffer, 1024);
	}
}
*/

void	draw_triangle(t_mlx *mlx, t_vec2d pos, t_vec2d v, uint32_t color)
{
	t_vec2d	org;

	org = pos;
	pos.y += v.y;
	draw_line(mlx, org, pos, color); 
	org = pos;
	org.y--;
	org.x++;

	draw_line(mlx, org, pos, color); 
	draw_line(mlx, org, pos, color); 
	draw_line(mlx, org, pos, color); 
}

int	main(int argc, char **argv)
{
	t_mlx	*fdf;
	t_list	*lst;

	fdf = new_mlx(WIDTH, HEIGHT, "fdf");
	if (!fdf)
		return (1);
	lst = parse_map("maps/42.fdf");
	if (!lst)
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
	draw_triangle(fdf, org, v, WHITE);
	mlx_put_image_to_window(fdf->inst, fdf->wnd, fdf->img, 0, 0);
	mlx_loop(fdf->inst);
	delete_mlx(fdf);
	return (0);
}
