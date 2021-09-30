/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shape_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 07:01:51 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 09:11:29 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_shape_print(
				const char *const matrix_name,
				const t_matrix *const matrix)
{
	ft_printf("%-20s shape (%4lu, %4lu)\n", matrix_name, matrix->size.rows,
		matrix->size.columns);
	return ;
}
