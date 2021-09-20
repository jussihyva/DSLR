/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:42:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 11:19:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_add_double(
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
				= ((double **)vector->values)[i.rows][i.columns] + value;
		}
	}
	return ;
}
