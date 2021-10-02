/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_dot_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 23:12:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/02 21:56:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static double	matrix1_rows_multiple_matrix2_column_values(
							const size_t matrix2_rows,
							const double *const matrix1_row_values,
							const double **const matrix2_values,
							size_t matrix2_column)
{
	double		result;
	size_t		i;

	result = 0;
	i = -1;
	while (++i < matrix2_rows)
		result += matrix1_row_values[i] * matrix2_values[i][matrix2_column];
	return (result);
}

void	ft_matrix_dot_matrix(
						const t_matrix *const matrix1,
						const t_matrix *const matrix2,
						t_matrix *const new_matrix)
{
	t_vector_size	i;

	if (matrix1->size.columns == matrix2->size.rows
		&& matrix1->size.rows == new_matrix->size.rows
		&& matrix2->size.columns == new_matrix->size.columns)
	{
		i.rows = -1;
		while (++i.rows < matrix1->size.rows)
		{
			i.columns = -1;
			while (++i.columns < matrix2->size.columns)
			{
				((double **)new_matrix->values)[i.rows][i.columns]
					= matrix1_rows_multiple_matrix2_column_values(
						matrix2->size.rows,
						((const double **const)matrix1->values)[i.rows],
						(const double **const)matrix2->values,
						i.columns);
			}
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector dot request!");
	return ;
}
