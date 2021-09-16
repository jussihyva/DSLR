/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dot_vector_double.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 23:12:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/16 23:50:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static double	matrix_row_multiple_vector_values(
							size_t length,
							double *matrix_row_values,
							double **vector_values)
{
	double		result;
	size_t		i;

	result = 0;
	i = -1;
	while (++i < length)
		result += matrix_row_values[i] * vector_values[i][0];
	return (result);
}

void	ft_matrix_dot_vector_double(
							const t_matrix *const matrix,
							const t_vector *const vector,
							t_vector *const new_vector)
{
	size_t			i;

	i = -1;
	if (matrix->size.columns == vector->size.rows)
	{
		while (++i < matrix->size.rows)
		{
			((double **)new_vector->values)[i][0]
				= matrix_row_multiple_vector_values(vector->size.rows,
					((double **)matrix->values)[i], (double **)vector->values);
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector dot request!");
	return ;
}
