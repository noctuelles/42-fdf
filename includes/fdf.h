/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:12:47 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/25 22:56:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H


typedef struct	s_coord3d
{
	int	x;
	int	y;
	int	z;
}				t_coord3d;

/* coord3d.c  */

t_coord3d	*new_coord3d(int x, int y, int z);
void		del_coord3d(t_coord3d *coord);

/* parsing.c */

t_list		*parse_map(const char *path);

#endif
