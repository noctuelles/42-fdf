/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:54:38 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/06 15:12:55 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>

char	*read_line(int fd, char **line)
{
	*line = get_next_line(fd);
	return (*line);
}

static void	get_file_lines_len(char buffer[1024], t_mlx_data *data)
{
	size_t	i;
	int		is_in_digit;

	i = 0;
	is_in_digit = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (!is_in_digit)
		{
			if (buffer[i] == '-' && ft_isdigit(buffer[i + 1]))
				is_in_digit = 1;
			else if (ft_isdigit(buffer[i]))
				is_in_digit = 1;
			if (is_in_digit)
				data->line_len++;
		}
		else
		{
			if (buffer[i] == ' ')
				is_in_digit = 0;
		}
		i++;
	}
}

void	get_file_infos(int fd, t_mlx_data *data)
{
	ssize_t	rded;
	char	*nw_addr;
	char	buffer[1024];

	rded = read(fd, buffer, 1024);
	if (rded)
		get_file_lines_len(buffer, data);
	while (rded)
	{
		nw_addr = ft_strchr(buffer, '\n');
		if (nw_addr)
		{
			data->nbr_line++;
			buffer = nw_addr + 1;
		}
		else
			rded = read(fd, buffer, 1024);
	}
}
