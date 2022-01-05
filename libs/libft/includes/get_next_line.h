/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:06:24 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/26 00:38:16 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10024
# endif

# include <stddef.h>

/*		gnl_info structure.
 *
 *		line:			the dynamic string that'll be returnn.
 *		len:			the lenght to copy over line in the buffer.
 *		f_fullrd:		this flag is set to 1 if we read a '\n'.
 *		f_readd_err:	this flag is set if he read fails.
 *		f_malloc_err:	this flag is set if a malloc fails.
 */

typedef struct s_gnl_info
{
	char	*line;
	int		rded;
	size_t	len;
	int		f_fullrd;
	int		f_read_err;
	int		f_malloc_err;
}				t_gnl_info;

char	*strralloc(char *str, char *add, size_t add_len);
size_t	ft_strlen(const char *str);
int		get_cpy_len(const char *str, t_gnl_info *gnl_info);
char	*get_next_line(int fd);

#endif
