/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_div_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:38:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 18:08:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_double_div_vector(
						const double value,
						const t_vector *const vector,
						t_vector *const new_vector)
{
	t_vector_size	i;

	i.rows = -1;
	while (++i.rows < vector->size.rows)
	{
		i.columns = -1;
		while (++i.columns < vector->size.columns)
		{
			((double **)new_vector->values)[i.rows][i.columns]
				= value / ((double **)vector->values)[i.rows][i.columns];
		}
	}
	return ;
}
