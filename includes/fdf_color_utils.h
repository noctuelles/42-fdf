/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_color_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:19:04 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/25 13:41:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_COLOR_UTILS_H
# define FDF_COLOR_UTILS_H

# include <stdint.h>

typedef struct s_color_f
{
	float	red;
	float	green;
	float	blue;
}				t_color_f;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

static inline uint32_t	get_red(uint32_t x)
{
	return ((x >> 16) & 0xff);
}

static inline uint32_t	get_green(uint32_t x)
{
	return ((x >> 8) & 0xff);
}

static inline uint32_t	get_blue(uint32_t x)
{
	return (x & 0xff);
}

static inline uint32_t	new_color(uint32_t r, uint32_t g, uint32_t b)
{
	return (0xff << 24 | r << 16 | g << 8 | b);
}

#endif
