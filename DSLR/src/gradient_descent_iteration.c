/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/28 12:39:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_matrix	*ft_sigmoid(const t_matrix *const input)
{
	t_matrix	*predicted_exp;
	t_matrix	*predicted_add;
	t_matrix	*predicted_div;

	predicted_exp = ft_matrix_create(sizeof(double), input->size.rows,
			input->size.columns);
	predicted_add = ft_matrix_create(sizeof(double), input->size.rows,
			input->size.columns);
	predicted_div = ft_matrix_create(sizeof(double), input->size.rows,
			input->size.columns);
	ft_matrix_exp_double(input, predicted_exp, E_MINUS);
	ft_matrix_add_double(predicted_exp, 1, predicted_add);
	ft_double_div_vector(1, predicted_add, predicted_div);
	return (predicted_div);
}

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
	predicted = ft_matrix_create(sizeof(double), weight->size.rows,
			activation_input->size.columns);
	if (regression_type == E_LOGISTIC)
	{
		ft_matrix_dot_matrix(weight, activation_input, predicted_prel);
		ft_matrix_add_vector(predicted_prel, bias, predicted_add);
		predicted = ft_sigmoid(predicted_add);
		if (ft_log_get_level() <= LOG_DEBUG)
			print_shapes(activation_input, weight, predicted);
	}
	return (predicted);
}

static t_derivative	*derivative_calculate(
									const t_matrix *const activation_input,
									const t_vector *const residual)
{
	const t_vector		*residual_transposed;
	t_matrix			*weight_prel;
	const t_vector		*bias_prel;
	t_derivative		*derivative;

	residual_transposed = ft_vector_transpose(residual);
	derivative = ft_memalloc(sizeof(*derivative));
	weight_prel = ft_matrix_create(sizeof(double), activation_input->size.rows,
			residual->size.rows);
	derivative->weight = ft_matrix_create(sizeof(double),
			activation_input->size.rows, residual->size.rows);
	derivative->bias = ft_vector_create(sizeof(double), residual->size.rows,
			E_DIR_ROW);
	ft_matrix_dot_matrix(activation_input, residual_transposed,
		weight_prel);
	ft_vector_div_double(weight_prel, activation_input->size.columns,
		derivative->weight);
	bias_prel = ft_matrix_sum(residual, E_DIR_ROW);
	ft_vector_div_double(bias_prel, activation_input->size.columns,
		derivative->bias);
	if (ft_log_get_level() <= LOG_DEBUG)
	{
		ft_matrix_print("derivative weight", derivative->weight, E_DOUBLE);
		ft_matrix_print("BIAS", derivative->bias, E_DOUBLE);
	}
	return (derivative);
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
			-= 0.01 * ((double **)derivative->bias->values)[i.rows][0];
		i.columns = -1;
		while (++i.columns < weight->size.columns)
		{
			((double **)weight->values)[i.rows][i.columns]
				-= 0.01 * ((double **)derivative->weight
					->values)[i.rows][i.columns];
		}
	}
	return ;
}

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							t_gradient_descent *const gradient_descent)
{
	const t_matrix	*predicted;
	const t_matrix	*residual;
	const t_vector	*residual_sum;
	t_derivative	*derivative;
	const t_vector	*cost;
	size_t			i;

	if (regression_type == E_LOGISTIC)
	{
		i = 0;
		while (++i <= 5000)
		{
			predicted = predict(regression_type,
					gradient_descent->input_values, gradient_descent->bias,
					gradient_descent->weight);
			residual = residual_calculate(gradient_descent->observed,
					predicted);
			derivative = derivative_calculate(gradient_descent->input_values,
					residual);
			update_weight_and_bias(derivative, gradient_descent->weight,
				gradient_descent->bias);
			cost = cost_calculate(predicted, gradient_descent->observed);
			if (ft_log_get_level() <= LOG_DEBUG)
			{
				residual_sum = ft_matrix_sum(residual, E_DIR_ROW);
				ft_matrix_print("Residual sum", residual_sum, E_DOUBLE);
				ft_matrix_print("COST", cost, E_DOUBLE);
			}
		}
	}
	weight_bias_save(gradient_descent->weight, gradient_descent->bias);
	return ;
}
