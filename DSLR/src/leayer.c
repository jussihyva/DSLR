/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leayer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:19:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 13:34:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	print_shapes(
				const t_matrix *const activation_input,
				const t_matrix *const weight,
				const t_matrix *const activation_output)
{
	ft_shape_print("activation_input", activation_input);
	ft_shape_print("weight", weight);
	ft_shape_print("activation_output", activation_output);
	return ;
}

static void	update_weight_and_bias(
							const t_derivative *const derivative,
							t_vector *const weight,
							t_vector *const bias)
{
	t_vector_size	i;

	i.rows = -1;
	while (++i.rows < weight->size.rows)
	{
		((double **)bias->values)[i.rows][0]
			-= LEARNING_RATE * ((double **)derivative->bias->values)[i.rows][0];
		i.columns = -1;
		while (++i.columns < weight->size.columns)
		{
			((double **)weight->values)[i.rows][i.columns]
				-= LEARNING_RATE * ((double **)derivative->weight
					->values)[i.rows][i.columns];
		}
	}
	return ;
}

static const t_matrix	*predict(
							t_regression_type regression_type,
							const t_matrix *const activation_input,
							const t_vector *bias,
							const t_matrix *const weight)
{
	t_matrix			*predicted_prel;
	t_matrix			*predicted_add;
	const t_matrix		*predicted;

	predicted_prel = ft_matrix_create(sizeof(double), weight->size.rows,
			activation_input->size.columns);
	predicted_add = ft_matrix_create(sizeof(double), weight->size.rows,
			activation_input->size.columns);
	predicted = NULL;
	if (regression_type == E_LOGISTIC)
	{
		ft_matrix_dot_matrix(weight, activation_input, predicted_prel);
		ft_matrix_add_vector(predicted_prel, bias, predicted_add);
		predicted = ft_sigmoid(predicted_add);
		if (ft_log_get_level() <= LOG_DEBUG)
			print_shapes(activation_input, weight, predicted);
	}
	ft_matrix_remove(&predicted_prel);
	ft_matrix_remove(&predicted_add);
	return (predicted);
}

void	leayer_calculate(
				const t_regression_type regression_type,
				const t_gradient_descent *const gradient_descent,
				const t_derivative *const derivative)
{
	const t_matrix	*predicted;

	predicted = predict(regression_type,
			gradient_descent->input_values, gradient_descent->bias,
			gradient_descent->weight);
	derivative_recalculate(gradient_descent->input_values,
		gradient_descent->observed, predicted, derivative);
	update_weight_and_bias(derivative, gradient_descent->weight,
		gradient_descent->bias);
	cost_recalculate(predicted, gradient_descent->observed,
		gradient_descent->cost);
	ft_matrix_remove((t_matrix **)&predicted);
	return ;
}
