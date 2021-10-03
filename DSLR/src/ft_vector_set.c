/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:31:10 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/03 09:56:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_set(t_vector *const vector, const double value)
{
	t_vector_size	i;

	i.rows = -1;
	while (++i.rows < vector->size.rows)
	{
		i.columns = -1;
		while (++i.columns < vector->size.columns)
			((double **)vector->values)[i.rows][i.columns] = value;
	}
	return ;
}
