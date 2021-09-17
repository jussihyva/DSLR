/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 20:25:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_vector	*ft_sigmoid(const t_vector *const input_vector)
{
	t_vector	*prediction_exp;
	t_vector	*prediction_add;
	t_vector	*prediction_div;

	prediction_exp = ft_vector_create(sizeof(double), input_vector->size.rows);
	prediction_add = ft_vector_create(sizeof(double), input_vector->size.rows);
	prediction_div = ft_vector_create(sizeof(double), input_vector->size.rows);
	ft_vector_exp_double(input_vector, prediction_exp);
	ft_vector_add_double(prediction_exp, 1, prediction_add);
	ft_vector_div_double(prediction_add, 1, prediction_div);
	// ft_vector_print("Input vector", input_vector, E_DOUBLE);
	// ft_vector_print("Sigmod vector", prediction_div, E_DOUBLE);
	return (prediction_div);
}

static const t_vector	*predict(
							t_regression_type regression_type,
							const t_matrix *const matrix,
							const double b,
							const t_vector *const vector)
{
	t_vector	*prediction_prel;
	t_vector	*prediction_add;
	t_vector	*prediction;

	prediction_prel = ft_vector_create(sizeof(double), matrix->size.rows);
	prediction_add = ft_vector_create(sizeof(double), matrix->size.rows);
	prediction = ft_vector_create(sizeof(double), matrix->size.rows);
	if (regression_type == E_LOGISTIC)
	{
		ft_matrix_dot_vector_double(matrix, vector, prediction_prel);
		ft_vector_add_double(prediction_prel, b, prediction_add);
		ft_sigmoid(prediction_add);
	}
	return (prediction);
}

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							const t_gradient_descent *const gradient_descent)
{
	const t_vector	*prediction;
	// t_vector		*residual;
	// t_vector	*cost;

	if (regression_type == E_LOGISTIC)
	{
		prediction = predict(regression_type,
				gradient_descent->input_values, gradient_descent->b,
				gradient_descent->weigth_values);
		FT_LOG_WARN("Implementation of logistic regression"
			" function is ongoing %f", E_TRUE - 2.5);
	}
	return ;
}
