/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 13:28:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							const t_gradient_descent *const gradient_descent)
{
	t_derivative	*derivative;
	size_t			i;
	t_matrix_size	weight_size;
	t_vector_size	bias_size;

	weight_size.rows = gradient_descent->observed->size.rows;
	weight_size.columns = gradient_descent->input_values->size.rows;
	bias_size.rows = gradient_descent->observed->size.rows;
	bias_size.columns = 1;
	derivative = derivative_initialize(&weight_size, &bias_size);
	if (regression_type == E_LOGISTIC)
	{
		i = 0;
		while (++i <= ITERATION_LOOP)
		{
			leayer_calculate(regression_type, gradient_descent, derivative);
			if (ft_log_get_level() <= LOG_INFO)
				ft_matrix_print("COST", gradient_descent->cost, E_DOUBLE);
		}
	}
	ft_matrix_print("COST", gradient_descent->cost, E_DOUBLE);
	weight_bias_save(gradient_descent->weight, gradient_descent->bias);
	derivative_remove(&derivative);
	return ;
}
