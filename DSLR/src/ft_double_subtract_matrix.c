/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_subtract_matrix.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 23:05:31 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/26 23:08:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_double_subtract_matrix(
									const double value,
									const t_matrix *const matrix,
									t_matrix *const new_matrix)
{
	t_vector_size		i;

	if (matrix->size.columns == new_matrix->size.columns
		&& matrix->size.rows == new_matrix->size.rows)
	{
		i.rows = -1;
		while (++i.rows < matrix->size.rows)
		{
			i.columns = -1;
			while (++i.columns < matrix->size.columns)
			{
				((double **)new_matrix->values)[i.rows][i.columns]
					= value - ((double **)matrix->values)[i.rows][i.columns];
			}
		}
	}
	else
		FT_LOG_FATAL("Invalid value matrix subtract request!");
	return ;
}
