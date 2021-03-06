/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:12:47 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/29 16:17:40 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* Headers */

# include "libft.h"
# include <stdint.h>

/* Program constant */

# define START_COLOR 0xff053c44
# define END_COLOR   0xff00ff00

# define WIDTH  1700
# define HEIGHT 1000

/* Isometric angle in radian */

# define ANGLE_ISO 0.463646716

/* Window strings */

# define TITLE           "Wireframe (FdF) viewer"
# define HUD_TXT         "Wifreframe viewer"
# define TRANSLATION_TXT "Translate map"
# define MAP_ZOOM        "Zoom (+ / -)"
# define Z_FACTOR        "Z Factor (+ / -)"
# define ROTATE_MAP      "Rotate map (X, Y)"
# define OTHERS          "Rotate map (Z)"
# define MAP_INFO        "Map informations"
# define VERTICES        "Vertices  :" 
# define FILE_NAME       "File name :"
# define TILE_SIZE       "Tile size :"
# define ORG_X           "Org. (x)  :"
# define ORG_Y           "Org. (y)  :"
# define Z_OFFSET        "Z offset  :"
# define GRADIENT        "Gradient  :"
# define TO              "to"
# define ABOUT           "42 FdF V2.0.0"
# define ABOUT_2         "plouvel (plouvel@student.42.fr)"

/* Basic color */

# define CLR_BLACK      0xff000000
# define CLR_WHITE      0xffffffff
# define CLR_YELLOW     0xffffff00
# define CLR_RED        0xffff0000
# define CLR_GREEN      0xff00ff00
# define CLR_BLUE       0xff0000ff
# define CLR_DARK_GREY  0xff303030
# define CLR_LIGHT_GREY 0xffc0c0c0

/* Keybindings */

# define K_ESC   0xff1b

# define K_PLUS  0x3d
# define K_MINUS 0x2d

# define K_P     0x70

# define K_W     0x77
# define K_A     0x61
# define K_S     0x73
# define K_D     0x64

# define K_UP    0xff52
# define K_DOWN  0xff54
# define K_LEFT  0xff51
# define K_RIGHT 0xff53

# define K_PGUP  0xff55
# define K_PGDW  0xff56

# define K_R     0x72
# define K_E     0x65

# define K_O     0x6f

/* Misc */

# define FATAL      "{1;31}[FATAL]{0} : "
# define INFO       "{1;96}[INFO]{0} : "
# define WARNING    "{1;93}[WARNING]{0} : "
# define NEW_PROJ   "New projection (ID {31}%d{0} \"{32}%s{0}\") added !\
 Transform fonction at {93}%p{0}.\n" 
# define SET_PROJ   "Setting current projection to projection ID {32}%d{0}\n"
# define ERR_MALLOC      1
# define ERR_ARGC        2
# define ERR_MAP         3  
# define STR_ERR_MALLOC "Cannot allocate memory.\n"
# define STR_ERR_ARGC   "Invalid numbers of argument.\n\
 Usage : ./fdf <map_path>\n"
# define STR_ERR_MAP    "Error occur parsing your map.\
 Maybe check file path ?\n"

/* Projection macro */

# define ISO       0
# define ISO_STR   "Isometric (1/2 ratio)"
# define ORTHO     1
# define ORTHO_STR "Top orthogonal"

# define START_PROJ ISO

typedef struct s_vec3d
{
	int	x;
	int	y;
	int	z;
}				t_vec3d;

typedef struct s_vec2d
{
	int			x;
	int			y;
	uint32_t	color;
}				t_vec2d;

typedef struct s_key
{
	int		x;
	int		y;
}				t_key;

typedef struct s_bresenham
{
	int	d;
	int	sign;
	int	i;
}				t_bresenham;

typedef struct s_projection
{
	t_vec2d		(*transform)();
	int			id;
	const char	*name;
	t_vec2d		init_org;
	t_vec2d		org;
	size_t		init_tile_width;
	size_t		tile_width;
	double		last_alpha;
	double		alpha;
	double		sin_alpha;
	double		cos_alpha;
	double		last_beta;
	double		beta;
	double		sin_beta;
	double		cos_beta;
	double		last_gamma;
	double		gamma;
	double		sin_gamma;
	double		cos_gamma;
}				t_projection;

typedef struct s_mlx_data
{
	char			*file_name;
	int				**vertices;
	uint32_t		*gradient;
	t_projection	*curr_proj;
	t_list			*proj;
	size_t			nbr_vertices;
	size_t			elems_line;
	size_t			nbr_lines;
	float			z_scaling;
	int				min_z;
	int				max_z;
	double			cos_theta;
	double			sin_theta;
}				t_mlx_data;

typedef struct s_mlx
{
	t_mlx_data	data;
	void		*inst;
	void		*wnd;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_mlx;

/* parsing.c */

int						**parse_map(char *path, t_mlx_data *data);

/* mlx.c */

t_mlx					*new_mlx(uint16_t width, uint16_t height,
							const char *title);
void					wipe_render_scene(t_mlx *fdf);
void					delete_mlx(t_mlx *mlx);

/* line.c  */

void					draw_line(t_mlx *mlx, t_vec2d p1, t_vec2d p2,
							uint32_t color);

/* line_gradient.c */

void					draw_line_gradient(t_mlx *mlx, t_vec2d p1, t_vec2d p2);

/* vertices.c */

int						**alloc_vertices(size_t nbr_lines);
void					free_vertices(int **vertices);
int						fill_vertices(int fd, t_mlx_data *data);

/* file_utils.c */

char					*read_line(int fd, char **line);
size_t					get_file_nbr_lines(const char *path);

/* gradient.c */

uint32_t				*get_color_gradient(uint32_t start_color,
							uint32_t end_color, size_t size);

/* render.c */

void					render(t_mlx *fdf);
void					compute_angle(t_mlx_data *data);
void					rotate(t_vec3d *vec, t_mlx_data *data);

/* transformation.c */

t_vec2d					transform_iso(size_t tile_width, t_vec2d org,
							t_vec3d vec3d, t_mlx_data *data);
t_vec2d					transform_ortho(size_t tile_width, t_vec2d org,
							t_vec3d vec3d, t_mlx_data *data);

/* render_utils.c */

t_vec2d					get_center(t_mlx_data *data, size_t tile_width);
size_t					setup_map(t_mlx_data *data);

/* projection.c */

t_list					*add_projection(t_mlx_data *data, int id,
							const char *name, t_vec2d (*transform)());
void					set_projection(t_mlx_data *data, int id);

/* primitives.c */

void					draw_rect(t_mlx *mlx, t_vec2d rect, t_vec2d pos,
							uint32_t color);
void					draw_full_rect(t_mlx *mlx, t_vec2d rect, t_vec2d pos,
							uint32_t color);

/* hud.c */

void					draw_hud_bg(t_mlx *mlx);
void					draw_hud_static_text(t_mlx *mlx);

/* hud2.c */

void					draw_compass(t_mlx *mlx);
void					draw_gradient(t_mlx *mlx);

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
