/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 14:00:57 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/21 14:36:50 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	**alloc_vertices(size_t nbr_lines)
{
	int		**vertices;
	size_t	i;

	vertices = (int **) malloc((nbr_lines + 1) * sizeof(int *));
	if (!vertices)
		return (NULL);
	i = 0;
	while (i < (nbr_lines + 1))
		vertices[i++] = NULL;
	return (vertices);
}

void	free_vertices(int **vertices)
{
	size_t	i;

	i = 0;
	while (vertices[i] != NULL)
		free(vertices[i++]);
	free(vertices);
}
