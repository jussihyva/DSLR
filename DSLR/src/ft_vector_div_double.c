/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_div_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:13:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 19:17:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_div_double(
						t_matrix *vector,
						double value,
						t_matrix *new_vector)
{
	size_t			i;

	i = -1;
	while (++i < vector->size.rows)
	{
		((double **)new_vector->values)[i][0]
			= value / ((double **)vector->values)[i][0];
	}
	return ;
}
