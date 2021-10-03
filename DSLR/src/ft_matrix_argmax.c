/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_argmax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:12:20 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/03 10:09:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static t_vector	*row_based_argmax(const t_matrix *const matrix)
{
	t_vector		*max;
	t_vector		*argmax;
	t_vector_size	i;
	double			value;

	max = ft_vector_create(sizeof(double), matrix->size.rows, E_DIR_ROW);
	argmax = ft_vector_create(sizeof(double), matrix->size.rows, E_DIR_ROW);
	ft_vector_set(max, DBL_MIN);
	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			value = ((double **)matrix->values)[i.rows][i.columns];
			if (((double **)max->values)[i.rows][0] < value)
			{
				((double **)max->values)[i.rows][0] = value;
				((double **)argmax->values)[i.rows][0] = i.columns;
			}
		}
	}
	return (argmax);
}

const t_vector	*ft_matrix_argmax(
						const t_matrix *const matrix,
						const t_vector_type vector_type)
{
	const t_vector	*argmax;

	if (vector_type == E_DIR_ROW)
		argmax = row_based_argmax(matrix);
	else
	{
		argmax = ft_vector_create(sizeof(double), matrix->size.columns,
				E_DIR_COLUMN);
	}
	return (argmax);
}
