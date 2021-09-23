/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   residual.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:24:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/23 14:46:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	print_shapes(
				const t_matrix *const predicted_result,
				const t_matrix *const desired_result,
				const t_matrix *const residual)
{
	ft_shape_print("predicted_result", predicted_result);
	ft_shape_print("desired_result", desired_result);
	ft_shape_print("residual", residual);
	ft_vector_print("residual", residual, E_DOUBLE);
	return ;
}

const t_vector	*residual_calculate(
						const t_vector *const observed,
						const t_vector *const predicted)
{
	t_vector	*residual;

	residual = ft_vector_create(sizeof(double), observed->size.columns,
			E_DIR_COLUMN);
	ft_vector_subtract_vector_double(predicted, observed, residual);
	print_shapes(predicted, observed, residual);
	return (residual);
}
