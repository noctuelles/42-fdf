/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 21:02:46 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/24 01:23:43 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

/*	read_fd read from a given file descriptor.
 *
 *	If there's an allocation error on the previous malloc or the read is done,
 *	it returns 0. Also, if the read failed, it returns 0.
 *	Else, it returns 1 (read sucessfull and).
 */

static int	read_fd(int fd, char *buffer, t_gnl_info *gnl_info)
{
	if (gnl_info->f_malloc_err || gnl_info->f_fullrd)
		return (0);
	gnl_info->rded = read(fd, buffer, BUFFER_SIZE);
	if (gnl_info->rded == -1)
	{
		gnl_info->f_read_err = 1;
		return (0);
	}
	if (gnl_info->rded == 0)
		return (0);
	buffer[gnl_info->rded] = '\0';
	return (1);
}

static void	strdelete(char **str)
{
	if (!str)
		return ;
	free(*str);
	*str = NULL;
}

/*	buffer_shift shift the buffer according to what we need to copy into
 *	our line.
 *
 *	Exemple are the best explanation:
 *
 * BUFFER_SIZE = 12
 *
 *	Line : NULL
 *	Buffer: "Hello\nHow ar\0"
 *	After buffer shift: "How ar\0\0\0\0\0\0"
 *	Line : "Hello\n"
 *
 *	-- GNL next instance --
 *
 *	Line : NULL
 *	Buffer: "How ar\0\0\0\0\0\0"
 *	After buffer shift : "\0\0\0\0\0\0\0\0\0\0\0\0"
 *	Line : "How ar\0"
 */

char	*buffer_shift(char *buffer, t_gnl_info *gnl_info)
{
	size_t	i;
	size_t	cnbr;

	i = 0;
	gnl_info->line = strralloc(gnl_info->line, buffer, gnl_info->len);
	if (!gnl_info->line)
	{
		gnl_info->f_malloc_err = 1;
		return (NULL);
	}
	if (gnl_info->f_fullrd && gnl_info->len != BUFFER_SIZE)
	{
		cnbr = ft_strlen(&buffer[gnl_info->len]);
		while (i < cnbr)
		{
			buffer[i] = buffer[i + gnl_info->len];
			i++;
		}
	}
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
	return (gnl_info->line);
}

/*	buffer_data_remains check if there data remaining in the buffer.
 *
 *	It checks two things :
 *
 *		If there's any new line on the buffer, it's a full read : we don't need
 *		to call read another time because we can already make a line with the c-
 *		-ontent stored in the buffer.
 *
 *		If there's no new line, it's not a full read therefore we need to call
 *		read again. So we copy what's stored into the buffer into our line,
 *		and proceed to reading the file descriptor.
 */

char	*buffer_data_remains(char *buffer, t_gnl_info *gnl_info)
{
	size_t	bufflen;

	bufflen = ft_strlen(buffer);
	gnl_info->line = NULL;
	gnl_info->rded = bufflen;
	gnl_info->len = 0;
	gnl_info->f_fullrd = 0;
	gnl_info->f_read_err = 0;
	gnl_info->f_malloc_err = 0;
	if (bufflen == 0)
		return (NULL);
	get_cpy_len(buffer, gnl_info);
	buffer_shift(buffer, gnl_info);
	return (gnl_info->line);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	t_gnl_info	gnl_info;

	if (fd < 0 || fd > 1023)
		return (NULL);
	buffer_data_remains(buffer[fd], &gnl_info);
	while (read_fd(fd, buffer[fd], &gnl_info))
	{
		get_cpy_len(buffer[fd], &gnl_info);
		buffer_shift(buffer[fd], &gnl_info);
	}
	if (gnl_info.f_read_err)
		strdelete(&gnl_info.line);
	return (gnl_info.line);
}
