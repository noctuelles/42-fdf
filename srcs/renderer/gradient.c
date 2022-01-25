/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:38:59 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/25 14:36:02 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "fdf_color_utils.h"
#include <stdlib.h>

uint32_t	*get_color_gradient(uint32_t start_color, uint32_t end_color,
		size_t size)
{
	uint32_t	*gradient;
	t_color_f	color_inc;
	t_color		color;
	size_t		i;

	gradient = (uint32_t *) malloc(size * sizeof(uint32_t));
	if (!gradient)
		return (NULL);
	i = 0;
	color.red = get_red(end_color) - get_red(start_color);
	color.green = get_green(end_color) - get_green(start_color);
	color.blue = get_blue(end_color) - get_blue(start_color);
	color_inc.red = (float) color.red / size;
	color_inc.green = (float) color.green / size;
	color_inc.blue = (float) color.blue / size;
	while (i < size)
	{
		gradient[i] = new_color(get_red(start_color) + (i + 1) * color_inc.red,
				get_green(start_color) + (i + 1) * color_inc.green,
				get_blue(start_color) + (i + 1) * color_inc.blue);
		i++;
	}
	return (gradient);
}
