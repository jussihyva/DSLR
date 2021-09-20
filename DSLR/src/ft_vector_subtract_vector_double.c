/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_subtract_vector_double.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/18 17:46:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_subtract_vector_double(
									const t_vector *const vector1,
									const t_vector *const vector2,
									t_vector *const new_vector)
{
	size_t			i;

	if (vector1->size.rows == vector2->size.rows
		&& vector1->size.rows == new_vector->size.rows)
	{
		i = -1;
		while (++i < vector1->size.rows)
		{
			((double **)new_vector->values)[i][0]
				= ((double **)vector1->values)[i][0]
				- ((double **)vector2->values)[i][0];
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector subtract request!");
	return ;
}
