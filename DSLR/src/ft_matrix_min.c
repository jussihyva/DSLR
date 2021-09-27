/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_min.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:05:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/27 12:15:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_vector	*min_row_based(const t_matrix *const matrix)
{
	const t_vector		*min_vector;
	t_vector_size		i;

	min_vector = ft_vector_create(sizeof(double), matrix->size.rows, E_DIR_ROW);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			((double **)min_vector->values)[i.rows][0]
				= ft_min_double(((double **)matrix->values)[i.rows][i.columns],
					((double **)min_vector->values)[i.rows][0]);
		}
	}
	return (min_vector);
}

static const t_vector	*min_column_based(const t_matrix *const matrix)
{
	const t_vector		*min_vector;
	t_vector_size		i;

	min_vector = ft_vector_create(sizeof(double), matrix->size.columns,
			E_DIR_COLUMN);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			((double **)min_vector->values)[0][i.columns]
				= ft_min_double(((double **)matrix->values)[i.rows][i.columns],
					((double **)min_vector->values)[0][i.columns]);
		}
	}
	return (min_vector);
}

const t_vector	*ft_matrix_min(
				const t_matrix *const matrix,
				const t_vector_type vector_type)
{
	const t_vector		*min_vector;

	if (vector_type == E_DIR_ROW)
		min_vector = min_row_based(matrix);
	else
		min_vector = min_column_based(matrix);
	return (min_vector);
}
