/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   residual.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:24:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/24 15:16:58 by jkauppi          ###   ########.fr       */
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
	// ft_vector_print("residual", residual, E_DOUBLE);
	return ;
}

const t_matrix	*residual_calculate(
						const t_matrix *const observed,
						const t_matrix *const predicted)
{
	t_matrix	*residual;

	residual = ft_matrix_create(sizeof(double), observed->size.rows,
			observed->size.columns);
	ft_matrix_subtract_matrix(predicted, observed, residual);
	if (ft_log_get_level() <= LOG_DEBUG)
		print_shapes(predicted, observed, residual);
	return (residual);
}
