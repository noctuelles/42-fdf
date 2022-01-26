/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 23:05:49 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/26 23:48:57 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <math.h>

static t_projection	*new_projection(int id, t_vec2d (*transform)())
{
	t_projection	*proj;

	proj = (t_projection *) malloc(sizeof(t_projection));
	if (!proj)
		return (NULL);
	ft_memset(proj, 0, sizeof(t_projection));
	proj->transform = transform;
	proj->id = id;
	proj->sin_alpha = sin(proj->alpha);
	proj->cos_alpha = cos(proj->alpha);
	proj->sin_beta = sin(proj->beta);
	proj->cos_beta = cos(proj->beta);
	proj->sin_gamma = sin(proj->gamma);
	proj->cos_gamma = cos(proj->gamma);
	return (proj);
}

t_list	*add_projection(t_mlx_data *data, int id, t_vec2d (*transform)())
{
	t_projection	*proj;
	t_list			*new;

	proj = new_projection(id, transform);
	if (!proj)
		return (NULL);
	new = ft_lstnew((void *) proj);
	if (!new)
		return (NULL);
	ft_lstadd_back(&data->proj, new);
	ft_printf("New projection (ID %d) added ! Transform fonction at %p.\n",
					id, transform);
	return (data->proj);
}

void	set_projection(t_mlx_data *data, int id)
{
	t_list			*lst;
	t_projection	*proj;

	lst = data->proj;
	while (lst)
	{
		proj = (t_projection *) lst->content;
		if (proj->id == id)
			data->curr_proj = proj;
		lst = lst->next;
	}
}
