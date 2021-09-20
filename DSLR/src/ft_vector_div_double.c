/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_div_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:13:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 18:09:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_div_double(
						const t_vector *const vector,
						const double value,
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
				= ((double **)vector->values)[i.rows][i.columns] / value;
		}
	}
	return ;
}
