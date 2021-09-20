/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 07:11:45 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 18:07:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

double	ft_vector_sum(const t_vector *const vector)
{
	double			sum;
	t_vector_size	i;

	sum = 0;
	i.rows = -1;
	while (++i.rows < vector->size.rows)
	{
		i.columns = -1;
		while (++i.columns < vector->size.columns)
		{
			sum += ((double **)vector->values)[i.rows][i.columns];
		}
	}
	return (sum);
}
