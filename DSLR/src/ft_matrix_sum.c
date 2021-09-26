/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 07:11:45 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/26 09:33:07 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_vector	*sum_row_based(const t_matrix *const matrix)
{
	const t_vector		*sum_vector;
	t_vector_size	i;

	sum_vector = ft_vector_create(sizeof(double), matrix->size.rows, E_DIR_ROW);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			((double **)sum_vector->values)[i.rows][0]
				+= ((double **)matrix->values)[i.rows][i.columns];
		}
	}
	return (sum_vector);
}

static const t_vector	*sum_column_based(const t_matrix *const matrix)
{
	const t_vector		*sum_vector;
	t_vector_size	i;

	sum_vector = ft_vector_create(sizeof(double), matrix->size.columns,
			E_DIR_COLUMN);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			((double **)sum_vector->values)[0][i.columns]
				+= ((double **)matrix->values)[i.rows][i.columns];
		}
	}
	return (sum_vector);
}

const t_vector	*ft_matrix_sum(
				const t_matrix *const matrix,
				const t_vector_type vector_type)
{
	const t_vector		*sum_vector;

	if (vector_type == E_DIR_ROW)
		sum_vector = sum_row_based(matrix);
	else
		sum_vector = sum_column_based(matrix);
	return (sum_vector);
}
