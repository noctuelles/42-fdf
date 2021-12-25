/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 17:16:49 by plouvel           #+#    #+#             */
/*   Updated: 2021/12/24 01:23:52 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	get_cpy_len(const char *str, t_gnl_info *gnl_info)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
		if (str[len - 1] == '\n')
		{
			gnl_info->f_fullrd = 1;
			gnl_info->len = len;
			return (1);
		}
	}
	gnl_info->f_fullrd = 0;
	gnl_info->len = gnl_info->rded;
	return (0);
}

static size_t	cpynfree(char *dest, char *src)
{
	size_t	i;

	if (!dest || !src)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	free(src);
	return (i);
}

static char	*strncpy_offset(char *dest, char *src, size_t offset, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < len)
	{
		dest[offset + i] = src[i];
		i++;
	}
	dest[offset + i] = '\0';
	return (dest);
}

char	*strralloc(char *str, char *add, size_t add_len)
{
	char	*nstr;
	size_t	size;
	size_t	offset;

	offset = 0;
	if ((!add || add[0] == '\0' || add_len == 0) && str)
		return (str);
	if (!str)
		size = add_len + 1;
	else
		size = add_len + ft_strlen(str) + 1;
	nstr = (char *) malloc(size * sizeof(char));
	if (!nstr)
	{
		free(str);
		return (NULL);
	}
	if (str)
		offset = cpynfree(nstr, str);
	strncpy_offset(nstr, add, offset, add_len);
	return (nstr);
}
