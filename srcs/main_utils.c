/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouvel <plouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:49:19 by plouvel           #+#    #+#             */
/*   Updated: 2022/01/28 14:33:12 by plouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"

int	raise_errors(t_mlx *fdf, int errcode)
{
	if (errcode == ERR_MALLOC)
		ft_printf(FATAL STR_ERR_MALLOC);
	else if (errcode == ERR_ARGC)
		ft_printf(WARNING STR_ERR_ARGC);
	else if (errcode == ERR_MAP)
		ft_printf(FATAL STR_ERR_MAP);
	if (fdf)
		delete_mlx(fdf);
	return (errcode);
}
