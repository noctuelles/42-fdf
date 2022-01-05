/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:14:14 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/05 13:32:41 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static char	*read_line(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line);
}

static void	free_values(char **values)
{
	size_t	i;

	i = 0;
	while (values[i] != NULL)
		free(values[i++]);
	free(values);
}

static int	fill_list_from_values(t_list **lst, char **values, unsigned int y)
{
	int	x;
	int	z;

	x = 0;
	while (values[x] != NULL)
	{
		z = ft_atoi(values[x]);
		ft_lstadd_back(lst, ft_lstnew(new_coord3d(x, y, z)));
		if (!lst)
			return (-1);
		x++;
	}
	return (0);
}

static t_list	*fill_list(int fd)
{
	unsigned int	y;
	t_list			*lst;
	char			*line;
	char			**values;

	y = 0;
	lst = NULL;
	while (read_line(fd, &line) != NULL)
	{
		values = ft_split(line, ' ');
		if (!values)
			return (NULL);
		if (fill_list_from_values(&lst, values, y) == -1)
			return (NULL);
		free_values(values);
		free(line);
		y++;
	}
	return (lst);
}

t_list	*parse_map(const char *path)
{
	int			fd;
	t_list		*lst;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	lst = fill_list(fd);
	return (lst);
}
