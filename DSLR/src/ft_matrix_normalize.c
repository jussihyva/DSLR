/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_normalize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 09:48:50 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 14:30:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

const t_matrix	*ft_matrix_normalize(
							const t_matrix *const matrix,
							const t_vector_type vector_type)
{
	t_matrix			*matrix_normalized;
	t_matrix			*matrix_normalized_prel;
	const t_vector		*min_value;
	const t_vector		*max_value;
	t_vector			*range;

	min_value = ft_matrix_min(matrix, E_DIR_ROW);
	max_value = ft_matrix_max(matrix, E_DIR_ROW);
	range = ft_vector_create(sizeof(double), matrix->size.rows, E_DIR_ROW);
	ft_matrix_subtract_matrix(max_value, min_value, range);
	matrix_normalized_prel = ft_matrix_create(sizeof(double), matrix->size.rows,
			matrix->size.columns);
	matrix_normalized = ft_matrix_create(sizeof(double), matrix->size.rows,
			matrix->size.columns);
	if (vector_type == E_DIR_ROW)
	{
		ft_matrix_subtract_vector(matrix, min_value, matrix_normalized_prel);
		ft_matrix_div_vector(matrix_normalized_prel, range, matrix_normalized);
	}
	ft_matrix_remove(&matrix_normalized_prel);
	ft_matrix_remove((t_matrix **)&min_value);
	ft_matrix_remove((t_matrix **)&max_value);
	ft_vector_remove(&range);
	return (matrix_normalized);
}
