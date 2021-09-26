/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_multiply_matrix.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 23:24:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/26 23:25:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_matrix_multiply_matrix(
							const t_matrix *const matrix1,
							const t_matrix *const matrix2,
							t_matrix *const new_matrix)
{
	t_vector_size		i;

	if (matrix1->size.columns == matrix2->size.columns
		&& matrix1->size.columns == new_matrix->size.columns
		&& matrix1->size.rows == matrix2->size.rows
		&& matrix1->size.columns == new_matrix->size.columns
		&& matrix1->size.rows == new_matrix->size.rows)
	{
		i.rows = -1;
		while (++i.rows < matrix1->size.rows)
		{
			i.columns = -1;
			while (++i.columns < matrix1->size.columns)
			{
				((double **)new_matrix->values)[i.rows][i.columns]
					= ((double **)matrix1->values)[i.rows][i.columns]
					* ((double **)matrix2->values)[i.rows][i.columns];
			}
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector subtract request!");
	return ;
}
