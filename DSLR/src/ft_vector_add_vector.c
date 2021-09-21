/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add_vector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 08:28:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/21 08:42:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_add_vector(
						const t_vector *const vector1,
						const t_vector *const vector2,
						t_vector *const new_vector)
{
	t_vector_size	i;

	if (ft_memcmp(&vector1->size, &vector2->size, sizeof(vector1->size)))
		FT_LOG_FATAL("Invalid vector add request!");
	else
	{
		i.rows = -1;
		while (++i.rows < vector1->size.rows)
		{
			i.columns = -1;
			while (++i.columns < vector1->size.columns)
			{
				((double **)new_vector->values)[i.rows][i.columns]
					= ((double **)vector1->values)[i.rows][i.columns]
					+ ((double **)vector2->values)[i.rows][i.columns];
			}
		}
	}
	return ;
}
