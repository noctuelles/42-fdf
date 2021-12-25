/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:55:02 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/25 22:55:32 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_coord3d	*new_coord3d(int x, int y, int z)
{
	t_coord3d	*coord;

	coord = (*t_coord3d) malloc(sizeof(t_coord3d));
	if (!coord)
		return (NULL);
	coord->x = x;
	coord->y = y;
	coord->z = z;
	return (coord);
}

void	del_coord3d(t_coord3d *coord)
{
	free(coord);
}
