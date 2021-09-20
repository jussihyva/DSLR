/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_sum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 07:11:45 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/19 07:14:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

double	ft_vector_sum(const t_vector *const vector)
{
	double		sum;
	size_t		i;

	sum = 0;
	i = -1;
	while (++i < vector->size.rows)
		sum += ((double **)vector->values)[i][0];
	return (sum);
}
