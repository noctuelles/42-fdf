/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:55:02 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/01 13:20:49 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

t_vec3d	*new_coord3d(int x, int y, int z)
{
	t_vec3d	*coord;

	coord = (t_vec3d *) malloc(sizeof(t_vec3d));
	if (!coord)
		return (NULL);
	coord->x = x;
	coord->y = y;
	coord->z = z;
	return (coord);
}

void	del_coord3d(t_vec3d *coord)
{
	free(coord);
}
