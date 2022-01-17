/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:05:35 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/17 19:47:23 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vec2d	transform_isometric(size_t tile_width, t_vec2d org, t_vec3d vec3d)
{
	t_vec2d	proj;
	size_t	tile_height;

	tile_height = tile_width / 2;
	proj.x = (vec3d.x - vec3d.y) * (tile_width / 2);
	proj.y = -vec3d.z * (tile_height / 2) + (vec3d.x + vec3d.y) * (tile_height / 2);
	proj.x += org.x;
	proj.y += org.y;
	return (proj);
}
