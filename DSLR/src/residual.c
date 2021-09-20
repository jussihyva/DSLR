/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   residual.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:24:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/19 07:26:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

const t_vector	*residual_calculate(
						const t_vector *const observed,
						const t_vector *const predicted)
{
	t_vector	*residual;

	residual = ft_vector_create(sizeof(double), observed->size.rows);
	ft_vector_subtract_vector_double(predicted, observed, residual);
	return (residual);
}
