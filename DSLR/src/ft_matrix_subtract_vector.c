/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_subtract_vector.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:27:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/27 13:30:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_matrix_subtract_vector(
									const t_matrix *const matrix,
									const t_vector *const vector,
									t_matrix *const new_matrix)
{
	t_vector_size		i;

	if (matrix->size.columns == new_matrix->size.columns
		&& matrix->size.rows == vector->size.rows
		&& matrix->size.rows == new_matrix->size.rows)
	{
		i.rows = -1;
		while (++i.rows < matrix->size.rows)
		{
			i.columns = -1;
			while (++i.columns < matrix->size.columns)
			{
				((double **)new_matrix->values)[i.rows][i.columns]
					= ((double **)matrix->values)[i.rows][i.columns]
					- ((double **)vector->values)[i.rows][0];
			}
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector subtract request!");
	return ;
}
