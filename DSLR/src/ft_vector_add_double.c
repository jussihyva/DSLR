/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:42:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 07:49:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_add_double(
						t_matrix *vector,
						double value_to_add,
						t_matrix *new_vector)
{
	size_t			i;

	i = -1;
	while (++i < vector->size.rows)
	{
		((double **)new_vector->values)[i][0]
			= ((double **)vector->values)[i][0] + value_to_add;
	}
	return ;
}
