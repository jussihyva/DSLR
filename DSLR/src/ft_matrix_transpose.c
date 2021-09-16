/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_transpose.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 23:54:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 00:26:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

t_matrix	*ft_matrix_transpose(const t_matrix *const matrix)
{
	t_matrix	*new_matrix;
	size_t		i;
	size_t		j;

	new_matrix = (t_matrix *)ft_memalloc(sizeof(*new_matrix));
	new_matrix->size.rows = matrix->size.columns;
	new_matrix->size.columns = matrix->size.rows;
	new_matrix->values = ft_memalloc(sizeof(*new_matrix->values)
			* matrix->size.columns);
	i = -1;
	while (++i < new_matrix->size.rows)
	{
		new_matrix->values[i]
			= ft_memalloc(sizeof(double) * new_matrix->size.columns);
		j = -1;
		while (++j < new_matrix->size.columns)
			((double **)new_matrix->values)[i][j]
				= ((double **)matrix->values)[j][i];
	}
	return (new_matrix);
}
