/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_add_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:42:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/24 14:09:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_matrix_add_vector(
						const t_matrix *const matrix,
						const t_vector *const vector,
						t_matrix *const new_matrix)
{
	t_vector_size	i;

	if (matrix->size.rows == vector->size.rows
		&& vector->size.columns == 1)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			i.rows = -1;
			while (++i.rows < vector->size.rows)
			{
				((double **)new_matrix->values)[i.rows][i.columns]
					= ((double **)matrix->values)[i.rows][i.columns]
					+ ((double **)vector->values)[i.rows][0];
			}
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix add vector request!");
	return ;
}
