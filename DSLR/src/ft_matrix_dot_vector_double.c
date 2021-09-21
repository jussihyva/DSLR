/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dot_vector_double.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 07:49:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/21 08:04:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static double	matrix_row_multiple_vector_values(
							const size_t length,
							const double *const matrix_values,
							double **const vector_values)
{
	double		result;
	size_t		i;

	result = 0;
	i = -1;
	while (++i < length)
		result += matrix_values[i] * vector_values[i][0];
	return (result);
}

void	ft_matrix_dot_vector_double(
							const t_matrix *const matrix,
							const t_vector *const vector,
							t_vector *const new_vector)
{
	t_vector_size	i;

	if (matrix->size.columns == vector->size.rows
		&& matrix->size.rows == new_vector->size.rows)
	{
		i.rows = -1;
		while (++i.rows < matrix->size.rows)
		{
			((double **)new_vector->values)[i.rows][0]
				= matrix_row_multiple_vector_values(matrix->size.columns,
					((double **)matrix->values)[i.rows],
					(double **)vector->values);
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector dot request!");
	return ;
}
