/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_subtract_vector_double.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/23 14:41:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_subtract_vector_double(
									const t_vector *const vector1,
									const t_vector *const vector2,
									t_vector *const new_vector)
{
	t_vector_size		i;

	if (vector1->size.columns == vector2->size.columns
		&& vector1->size.columns == new_vector->size.columns &&
		vector1->size.rows == vector2->size.rows
		&& vector1->size.columns == new_vector->size.columns
		&& vector1->size.rows == new_vector->size.rows)
	{
		i.rows = -1;
		while (++i.rows < vector1->size.rows)
		{
			i.columns = -1;
			while (++i.columns < vector1->size.columns)
			{
				((double **)new_vector->values)[i.rows][i.columns]
					= ((double **)vector1->values)[i.rows][i.columns]
					- ((double **)vector2->values)[i.rows][i.columns];
			}
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector subtract request!");
	return ;
}
