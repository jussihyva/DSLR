/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:18:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/27 12:20:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_vector	*max_row_based(const t_matrix *const matrix)
{
	const t_vector		*max_vector;
	t_vector_size		i;

	max_vector = ft_vector_create(sizeof(double), matrix->size.rows, E_DIR_ROW);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			((double **)max_vector->values)[i.rows][0]
				= ft_max_double(((double **)matrix->values)[i.rows][i.columns],
					((double **)max_vector->values)[i.rows][0]);
		}
	}
	return (max_vector);
}

static const t_vector	*max_column_based(const t_matrix *const matrix)
{
	const t_vector		*max_vector;
	t_vector_size		i;

	max_vector = ft_vector_create(sizeof(double), matrix->size.columns,
			E_DIR_COLUMN);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			((double **)max_vector->values)[0][i.columns]
				= ft_min_double(((double **)matrix->values)[i.rows][i.columns],
					((double **)max_vector->values)[0][i.columns]);
		}
	}
	return (max_vector);
}

const t_vector	*ft_matrix_max(
				const t_matrix *const matrix,
				const t_vector_type vector_type)
{
	const t_vector		*max_vector;

	if (vector_type == E_DIR_ROW)
		max_vector = max_row_based(matrix);
	else
		max_vector = max_column_based(matrix);
	return (max_vector);
}
