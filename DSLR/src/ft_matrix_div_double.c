/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_div_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:13:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/02 22:18:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_matrix_div_double(
						const t_matrix *const matrix,
						const double value,
						t_matrix *const new_matrix)
{
	t_vector_size	i;

	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		while (++i.columns < matrix->size.columns)
		{
			((double **)new_matrix->values)[i.rows][i.columns]
				= ((double **)matrix->values)[i.rows][i.columns] / value;
		}
	}
	return ;
}
