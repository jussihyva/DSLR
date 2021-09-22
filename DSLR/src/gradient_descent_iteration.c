/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/22 15:59:09 by jkauppi          ###   ########.fr       */
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
							const t_vector *const weight)
{
	t_vector			*predicted_prel;
	t_vector			*predicted_add;
	const t_vector		*weight_transposed;
	const t_vector		*predicted;

	predicted_prel = ft_vector_create(sizeof(double), matrix->size.columns);
	predicted_add = ft_vector_create(sizeof(double), matrix->size.columns);
	predicted = ft_vector_create(sizeof(double), matrix->size.columns);
	if (regression_type == E_LOGISTIC)
	{
		weight_transposed = ft_vector_transpose(weight);
		ft_vector_dot_matrix_double(weight_transposed, matrix, predicted_prel);
		ft_vector_add_double(predicted_prel, bias, predicted_add);
		predicted = ft_sigmoid(predicted_add);
	}
	return (predicted);
}

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							t_gradient_descent *const gradient_descent)
{
	const t_vector	*predicted;
	const t_vector	*residual;
	const t_vector	*residual_transpose;
	t_vector		*residual_abs;
	t_vector		*d_weight_prel;
	t_vector		*d_weight;
	t_vector		*d_weight_delta;
	t_vector		*new_weight;
	double			cost;
	size_t			i;

	if (regression_type == E_LOGISTIC)
	{
		i = 0;
		while (++i <= 50)
		{
			predicted = predict(regression_type,
					gradient_descent->input_values, gradient_descent->bias,
					gradient_descent->weight);
			residual = residual_calculate(gradient_descent->observed,
					predicted);
			residual_transpose = ft_vector_transpose(residual);
			d_weight_prel = ft_vector_create(sizeof(double),
					gradient_descent->input_values->size.rows);
			d_weight = ft_vector_transpose(d_weight_prel);
			d_weight_delta = ft_vector_transpose(d_weight_prel);
			new_weight = ft_vector_transpose(d_weight_prel);
			ft_matrix_dot_vector_double(gradient_descent->input_values,
				residual_transpose, d_weight);
			residual_abs = ft_vector_create(sizeof(double),
					residual->size.columns);
			ft_vector_abs_double(residual, residual_abs);
			ft_vector_div_double(d_weight,
				gradient_descent->input_values->size.columns / 0.01,
				d_weight_delta);
			cost = ft_vector_sum(residual_abs) / residual_abs->size.columns;
			ft_printf("COST: %f\n", cost);
			ft_vector_add_vector(gradient_descent->weight, d_weight_delta,
				new_weight);
			ft_vector_print("Delta weight", new_weight, E_DOUBLE);
			gradient_descent->bias += ft_vector_sum(residual)
				/ gradient_descent->input_values->size.columns / 0.01;
			gradient_descent->weight->values = new_weight->values;
		}
	}
	return ;
}
