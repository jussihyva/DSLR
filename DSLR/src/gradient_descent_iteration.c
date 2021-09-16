/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 00:24:51 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	predicted_output_calculate(
								t_regression_type regression_type,
								const t_matrix *const matrix,
								const t_vector *const vector,
								t_vector *const predicted_output)
{
	if (regression_type == E_LOGISTIC)
	{
		ft_matrix_dot_vector_double(matrix, vector, predicted_output);
	}
	return ;
}

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							const t_gradient_descent *const gradient_descent)
{
	t_vector		*weigth_values_transposed;
	const t_vector	*predicted_output;
	t_vector		*predicted_output_transposed;
	// t_vector	*cost;

	predicted_output = ft_vector_create(sizeof(double),
			gradient_descent->input_values->size.rows);
	predicted_output_transposed = ft_vector_transpose(predicted_output);
	if (regression_type == E_LOGISTIC)
	{
		weigth_values_transposed
			= ft_vector_transpose(gradient_descent->weigth_values);
		predicted_output_calculate(regression_type,
			gradient_descent->input_values, weigth_values_transposed,
			predicted_output_transposed);
		FT_LOG_WARN("Implementation of logistic regression"
			" function is ongoing %f", E_TRUE - 2.5);
	}
	return ;
}
