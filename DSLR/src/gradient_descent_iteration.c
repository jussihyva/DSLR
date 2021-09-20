/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 11:51:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_vector	*ft_sigmoid(const t_vector *const input)
{
	t_vector	*predicted_exp;
	t_vector	*predicted_add;
	t_vector	*predicted_div;

	predicted_exp = ft_vector_create(sizeof(double), input->size.columns);
	predicted_add = ft_vector_create(sizeof(double), input->size.columns);
	predicted_div = ft_vector_create(sizeof(double), input->size.columns);
	ft_vector_exp_double(input, predicted_exp, E_MINUS);
	ft_vector_add_double(predicted_exp, 1, predicted_add);
	ft_double_div_vector(1, predicted_add, predicted_div);
	// ft_vector_print("Input vector", input_vector, E_DOUBLE);
	// ft_vector_print("Sigmod vector", predicted_div, E_DOUBLE);
	return (predicted_div);
}

static const t_vector	*predict(
							t_regression_type regression_type,
							const t_matrix *const matrix,
							const double bias,
							const t_vector *const weigth)
{
	t_vector		*predicted_prel;
	t_vector		*predicted_add;
	const t_vector	*predicted;

	predicted_prel = ft_vector_create(sizeof(double), matrix->size.columns);
	predicted_add = ft_vector_create(sizeof(double), matrix->size.columns);
	predicted = ft_vector_create(sizeof(double), matrix->size.columns);
	if (regression_type == E_LOGISTIC)
	{
		ft_vector_dot_matrix_double(matrix, weigth, predicted_prel);
		ft_vector_add_double(predicted_prel, bias, predicted_add);
		predicted = ft_sigmoid(predicted_add);
	}
	return (predicted);
}

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							const t_gradient_descent *const gradient_descent)
{
	const t_vector	*predicted;
	const t_vector	*residual;
	t_vector		*residual_abs;
	double			cost;

	if (regression_type == E_LOGISTIC)
	{
		predicted = predict(regression_type,
				gradient_descent->input_values, gradient_descent->bias,
				gradient_descent->weigth);
		residual = residual_calculate(gradient_descent->observed, predicted);
		residual_abs = ft_vector_create(sizeof(double), residual->size.rows);
		ft_vector_abs_double(residual, residual_abs);
		cost = ft_vector_sum(residual_abs) / residual->size.rows;
		// ft_vector_print("Observed", gradient_descent->observed, E_DOUBLE);
		// ft_vector_print("Predicted", predicted, E_DOUBLE);
		ft_vector_print("Residual", residual_abs, E_DOUBLE);
		ft_printf("COST: %f\n", cost);
		FT_LOG_WARN("Implementation of logistic regression"
			" function is ongoing %f", E_TRUE - 2.5);
	}
	return ;
}
