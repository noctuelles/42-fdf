/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:12:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/14 17:13:21 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include <stdint.h>

# define DIM_GREY 0xff696969
# define WHITE 0xffffffff

# define WIDTH 1700
# define HEIGHT 1000

# define HUD_TXT "Wifreframe viewer"
# define TRANSLATION_TXT "Translate map"
# define MAP_ZOOM "Zoom (+ / -)"
# define Z_FACTOR "Z Factor (+ / -)"
# define ROTATE_MAP "Rotate map"
# define OTHERS "Others"
# define MAP_INFO "Map informations"
# define VERTICES  "Vertices  :" 
# define FILE_NAME "File name :"
# define TILE_SIZE "Tile size :"
# define ABOUT "42 FdF project"
# define ABOUT_2 "plouvel (plouvel@student.42.fr)"

# define CLR_WHITE 0xffffffff
# define CLR_DARK_GREY 0xff303030
# define CLR_LIGHT_GREY 0xffc0c0c0

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

typedef struct s_org_data
{
	t_vec2d	org;
	size_t	tile_width;
}				t_org_data;

typedef struct s_key
{
	int		x;
	int		y;
	char	*txt_key;
}				t_key;

typedef struct s_mlx_data
{
	const char	*file_name;
	int			**vertices;
	size_t		nbr_vertices;
	t_list		*keys;
	size_t		elems_line;
	size_t		nbr_lines;
	int			tile_width;
	t_vec2d		org;
	t_vec3d		edges[4];
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

int		**parse_map(const char *path, t_mlx_data *data);

/* mlx.c */

t_mlx		*new_mlx(uint16_t width, uint16_t height, const char *title);
void		put_pixel(t_mlx *mlx, int x, int y, uint32_t color);
uint32_t	get_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b);
void		delete_mlx(t_mlx *mlx);

/* line.c  */

void		draw_line(t_mlx *mlx, t_vec2d p1, t_vec2d p2, uint32_t color);

/* vertices.c */


int			**alloc_vertices(size_t nbr_lines);
void		free_vertices(int **vertices);
int			**fill_vertices(int fd, t_mlx_data *data);
void		print_vertices(t_mlx_data data);

/* math_utils.c */

int			ft_abs(int i);
void		render_isometric(t_mlx *fdf);

/* file_utils.c */

char		*read_line(int fd, char **line);
size_t		get_file_nbr_lines(const char *path);

/* render.c */

t_vec2d		transform_isometric(size_t tile_width, t_vec2d org, t_vec3d vec3d);

/* primitives.c */

void		draw_rect(t_mlx *mlx, t_vec2d rect, t_vec2d pos, uint32_t color);
void		draw_full_rect(t_mlx *mlx, t_vec2d rect, t_vec2d pos,
																uint32_t color);

/* hud.c */

void		draw_hud_bg(t_mlx *mlx);
void		draw_hud_static_text(t_mlx *mlx);

/* keys.c */

void		draw_keys(t_mlx *mlx);

static inline void	set_vec2d(t_vec2d *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

#endif
