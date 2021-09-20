/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_subtract_vector_double.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:35:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 18:18:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_subtract_vector_double(
									const t_vector *const vector1,
									const t_vector *const vector2,
									t_vector *const new_vector)
{
	size_t			i;

	if (vector1->size.columns == vector2->size.columns
		&& vector1->size.columns == new_vector->size.columns)
	{
		i = -1;
		while (++i < vector1->size.columns)
		{
			((double **)new_vector->values)[0][i]
				= ((double **)vector1->values)[0][i]
				- ((double **)vector2->values)[0][i];
		}
	}
	else
		FT_LOG_FATAL("Invalid matrix vector subtract request!");
	return ;
}
