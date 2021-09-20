/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_dot_matrix_double.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 23:12:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 18:16:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static double	matrix_row_multiple_vector_values(
							size_t length,
							double **matrix_values,
							size_t matrix_column,
							double *vector_values)
{
	double		result;
	size_t		i;

	result = 0;
	i = -1;
	while (++i < length)
		result += matrix_values[i][matrix_column] * vector_values[i];
	return (result);
}

void	ft_vector_dot_matrix_double(
							const t_vector *const vector,
							const t_matrix *const matrix,
							t_vector *const new_vector)
{
	t_vector_size	i;

	if (vector->size.columns == matrix->size.rows
		&& matrix->size.columns == new_vector->size.columns)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			((double **)new_vector->values)[0][i.columns]
				= matrix_row_multiple_vector_values(matrix->size.rows,
					((double **)matrix->values), i.columns,
					((double **)vector->values)[0]);
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector dot request!");
	return ;
}
