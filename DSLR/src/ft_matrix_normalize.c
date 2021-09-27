/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_normalize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:48:50 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/27 13:34:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

const t_matrix	*ft_matrix_normalize(
							const t_matrix *const matrix,
							const t_vector_type vector_type)
{
	t_matrix			*matrix_normalized;
	t_matrix			*matrix_normalized_prel;
	t_min_max_value		min_max_value;

	min_max_value.min_value = ft_matrix_min(matrix, E_DIR_ROW);
	min_max_value.max_value = ft_matrix_max(matrix, E_DIR_ROW);
	min_max_value.range = ft_vector_create(sizeof(double), matrix->size.rows,
			E_DIR_ROW);
	ft_matrix_subtract_matrix(min_max_value.max_value, min_max_value.min_value,
		min_max_value.range);
	matrix_normalized_prel = ft_matrix_create(sizeof(double), matrix->size.rows,
			matrix->size.columns);
	matrix_normalized = ft_matrix_create(sizeof(double), matrix->size.rows,
			matrix->size.columns);
	if (vector_type == E_DIR_ROW)
	{
		ft_matrix_subtract_vector(matrix, min_max_value.min_value,
			matrix_normalized_prel);
		ft_matrix_div_vector(matrix_normalized_prel, min_max_value.range,
			matrix_normalized);
	}
	return (matrix_normalized);
}
