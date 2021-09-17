/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 16:07:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_vector	*ft_sigmoid(const t_vector *const input_vector)
{
	t_vector	*predicted_output_exp;
	t_vector	*predicted_output_add;
	t_vector	*predicted_output_div;

	predicted_output_exp = ft_vector_create(sizeof(double),
			input_vector->size.rows);
	predicted_output_add = ft_vector_create(sizeof(double),
			input_vector->size.rows);
	predicted_output_div = ft_vector_create(sizeof(double),
			input_vector->size.rows);
	ft_vector_exp_double(input_vector, predicted_output_exp);
	ft_vector_add_double(predicted_output_exp, 1, predicted_output_add);
	// ft_vector_div_double(predicted_output_add, 1, predicted_output_div);
	return (predicted_output_div);
}

static const t_vector	*predicted_output_calculate(
								t_regression_type regression_type,
								const t_matrix *const matrix,
								const double b,
								const t_vector *const vector)
{
	t_vector	*predicted_output_prel;
	t_vector	*predicted_output_add;
	t_vector	*predicted_output;

	predicted_output_prel = ft_vector_create(sizeof(double), matrix->size.rows);
	predicted_output_add = ft_vector_create(sizeof(double), matrix->size.rows);
	predicted_output = ft_vector_create(sizeof(double), matrix->size.rows);
	if (regression_type == E_LOGISTIC)
	{
		ft_matrix_dot_vector_double(matrix, vector,
			predicted_output_prel);
		ft_vector_add_double(predicted_output_prel, b, predicted_output_add);
		ft_sigmoid(predicted_output_add);
	}
	return (predicted_output);
}

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							const t_gradient_descent *const gradient_descent)
{
	const t_vector	*predicted_output;
	// t_vector	*cost;

	if (regression_type == E_LOGISTIC)
	{
		predicted_output = predicted_output_calculate(regression_type,
				gradient_descent->input_values, gradient_descent->b,
				gradient_descent->weigth_values);
		FT_LOG_WARN("Implementation of logistic regression"
			" function is ongoing %f", E_TRUE - 2.5);
	}
	return ;
}
