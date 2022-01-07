/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:12:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/07 15:57:35 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include <stdint.h>

# define DIM_GREY 0xff696969
# define WHITE 0xffffffff

# define WIDTH 1700
# define HEIGHT 900
# define X_MID 1500 / 2
# define Y_MID 900 / 2

typedef struct	s_vec3d
{
	int	x;
	int	y;
	int	z;
}				t_vec3d;

typedef struct	s_vec2d
{
	int	x;
	int	y;
}				t_vec2d;

typedef struct s_mlx_data
{
	t_list		*vertices;
	size_t		elems_line;
	size_t		nbr_line;
	size_t		max_z;
	size_t		tile_width;
	size_t		vertice_size[2];
	uint16_t	width;
	uint16_t	height;
}				t_mlx_data;

typedef struct s_mlx
{
	void		*inst;
	void		*wnd;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_mlx_data	data;
}				t_mlx;

/* parsing.c */

char		*read_line(int fd, char **line);
t_list		*parse_map(const char *path, t_mlx_data *data);

/* mlx.c */

t_mlx		*new_mlx(uint16_t width, uint16_t height, const char *title);
void		put_pixel(t_mlx *mlx, int x, int y, uint32_t color);
uint32_t	get_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b);
void		delete_mlx(t_mlx *mlx);

/* line.c  */

void		draw_line(t_mlx *mlx, t_vec2d p1, t_vec2d p2, uint32_t color);

/* vertices.c */

t_list		*fill_vertices(int fd, t_mlx_data *data);

void		free_vertices(int **vertices, size_t index);
void		print_vertices(t_list *lst);

/* math_utils.c */

int			ft_abs(int i);

#endif
