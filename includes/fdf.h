/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:12:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/23 00:45:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include <stdint.h>

# define R(x) ((x >> 16) & 0xff)
# define G(x) ((x >> 8) & 0xff)
# define B(x) (x & 0xff)
# define SET_RED(x,r) (x & ~(0xff << 16)) | (r << 16)
# define SET_GREEN(x,g) (x & ~(0xff << 8)) | (g << 8)
# define SET_BLUE(x,b) (x & ~0xff) | b
# define NEW_COLOR(r,g,b) 0xff << 24 | r << 16 | g << 8 | b

# define LINE_COLOR 0xffffffff

# define WIDTH 1700
# define HEIGHT 1000

# define ANGLE_ISO 0.463646716

# define HUD_TXT "Wifreframe viewer"
# define TRANSLATION_TXT "Translate map"
# define MAP_ZOOM "Zoom (+ / -)"
# define Z_FACTOR "Z Factor (+ / -)"
# define ROTATE_MAP "Rotate map (X, Y)"
# define OTHERS "Rotate map (Z)"
# define MAP_INFO "Map informations"
# define VERTICES  "Vertices  :" 
# define FILE_NAME "File name :"
# define TILE_SIZE "Tile size :"
# define ORG_X     "Org. (x)  :"
# define ORG_Y     "Org. (y)  :"
# define Z_OFFSET  "Z offset  :"
# define Z_HEIGHT  "Z addon   :"
# define ABOUT "42 FdF project"
# define ABOUT_2 "plouvel (plouvel@student.42.fr)"

# define CLR_WHITE 0xffffffff
# define CLR_YELLOW 0xffffff00
# define CLR_DARK_GREY 0xff303030
# define CLR_LIGHT_GREY 0xffc0c0c0

# define K_ESC 0xff1b

# define K_PLUS 0x3d
# define K_MINUS 0x2d

# define K_W 0x77
# define K_A 0x61
# define K_S 0x73
# define K_D 0x64

# define K_UP 0xff52
# define K_DOWN 0xff54
# define K_LEFT 0xff51
# define K_RIGHT 0xff53

# define K_PGUP 0xff55
# define K_PGDW 0xff56

# define K_ALTGR 0xfe03
# define K_CRTL 0xffe4

# define FATAL "{1;31}[FATAL]{0} : "
# define WARNING "{1;93}[WARNING]{0} : "
# define ERR_MALLOC 1
# define STR_ERR_MALLOC "Cannot allocate memory."
# define ERR_ARGC 2
# define STR_ERR_ARGC "Invalid numbers of argument.\nUsage : ./fdf <map_path>\n"
# define ERR_MAP 3
# define STR_ERR_MAP "Error occur parsing your map. Maybe check file path ?\n"

typedef struct s_vec3d
{
	int	x;
	int	y;
	int	z;
}				t_vec3d;

typedef struct s_vec2d
{
	int		x;
	int		y;
	t_vec3d	from;
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
	char		*file_name;
	int			**vertices;
	uint32_t	*gradient;
	size_t		nbr_vertices;
	size_t		elems_line;
	size_t		nbr_lines;
	int			tile_width;
	float		z_scaling;
	t_vec2d		org;
	t_vec3d		edges[3];
	double		alpha;
	double		beta;
	double		gamma;
	double		cos_theta;
	double		sin_theta;
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

int						**parse_map(char *path, t_mlx_data *data);

/* mlx.c */

t_mlx					*new_mlx(uint16_t width, uint16_t height,
							const char *title);
uint32_t				get_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b);
void					wipe_render_scene(t_mlx *fdf);
void					delete_mlx(t_mlx *mlx);

/* line.c  */

void					draw_line(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
							uint32_t color);
void					draw_line_gradient(t_mlx *mlx, t_vec2d p1, t_vec2d p2);

/* vertices.c */

int						**alloc_vertices(size_t nbr_lines);
void					free_vertices(int **vertices);
int						**fill_vertices(int fd, t_mlx_data *data);

/* file_utils.c */

char					*read_line(int fd, char **line);
size_t					get_file_nbr_lines(const char *path);

/* render.c */

t_vec2d					transform_isometric(size_t tile_width, t_vec2d org,
							t_vec3d vec3d, t_mlx_data *data);
void					apply_isometric(t_mlx *fdf);

/* render_utils.c */

size_t					setup_map(t_mlx_data *data, t_vec3d medges[4],
							t_vec2d org_hud);

/* primitives.c */

void					draw_rect(t_mlx *mlx, t_vec2d rect, t_vec2d pos,
							uint32_t color);
void					draw_full_rect(t_mlx *mlx, t_vec2d rect, t_vec2d pos,
							uint32_t color);

/* hud.c */

void					draw_hud_bg(t_mlx *mlx);
void					draw_hud_static_text(t_mlx *mlx);

/* keys.c */

void					draw_keys(t_mlx *mlx);

/* main_utils.c */

int						key_handler(int keycode, t_mlx *fdf);
int						raise_errors(t_mlx *fdf, int errcode);

static inline void	set_vec2d(t_vec2d *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

static inline t_vec2d	new_vec2d(int x, int y)
{
	t_vec2d	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

static inline void	set_vec3d(t_vec3d *vec, int x, int y, int z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

static inline void	put_pixel(t_mlx *mlx, int x, int y, uint32_t color)
{
	char	*pixel_addr;

	pixel_addr = mlx->addr + (x * (mlx->bpp / 8) + y * mlx->line_len);
	*(uint32_t *)pixel_addr = color;
}

static inline int	ft_abs(int i)
{
	if (i >= 0)
		return (i);
	else
		return (-i);
}

#endif
