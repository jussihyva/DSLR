/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/24 15:05:26 by jkauppi          ###   ########.fr       */
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

static const t_vector	*predict(
							t_regression_type regression_type,
							const t_matrix *const matrix,
							const t_vector *bias,
							const t_matrix *const weight)
{
	t_matrix			*predicted_prel;
	t_matrix			*predicted_add;
	const t_matrix		*weight_transposed;
	const t_vector		*bias_transposed;
	const t_matrix		*predicted;

	predicted_prel = ft_matrix_create(sizeof(double), weight->size.columns,
			matrix->size.columns);
	predicted_add = ft_matrix_create(sizeof(double), weight->size.columns,
			matrix->size.columns);
	predicted = ft_matrix_create(sizeof(double), weight->size.columns,
			matrix->size.columns);
	if (regression_type == E_LOGISTIC)
	{
		weight_transposed = ft_vector_transpose(weight);
		bias_transposed = ft_vector_transpose(bias);
		ft_matrix_dot_matrix(weight_transposed, matrix, predicted_prel);
		ft_matrix_add_vector(predicted_prel, bias_transposed, predicted_add);
		predicted = ft_sigmoid(predicted_add);
		if (ft_log_get_level() <= LOG_DEBUG)
			print_shapes(matrix, weight, predicted);
	}
	return (predicted);
}

static t_derivative	*derivative_calculate(
									const t_matrix *const activation_input,
									const t_vector *const residual)
{
	const t_vector		*residual_transposed;
	t_vector			*weight_prel;
	t_derivative		*derivative;

	residual_transposed = ft_vector_transpose(residual);
	derivative = ft_memalloc(sizeof(*derivative));
	weight_prel = ft_vector_create(sizeof(double), activation_input->size.rows,
			E_DIR_ROW);
	derivative->weight = ft_vector_create(sizeof(double),
			activation_input->size.rows, E_DIR_ROW);
	ft_matrix_dot_vector_double(activation_input, residual_transposed,
		weight_prel);
	ft_vector_div_double(weight_prel, activation_input->size.columns,
		derivative->weight);
	derivative->bias = ft_vector_sum(residual);
	derivative->bias /= activation_input->size.columns;
	if (ft_log_get_level() <= LOG_DEBUG)
		ft_matrix_print("derivative weight", derivative->weight, E_DOUBLE);
	FT_LOG_DEBUG("BIAS: %f", derivative->bias);
	return (derivative);
}

static void	update_weight_and_bias(
							const t_derivative *const derivative,
							t_vector *const weight,
							t_vector *const bias)
{
	t_vector		*new_bias;
	t_vector_size	i;

	new_bias = ft_vector_create(sizeof(double), bias->size.columns,
			E_DIR_COLUMN);
	ft_vector_add_double(bias, 0.01 * derivative->bias, new_bias);
	bias->values = new_bias->values;
	i.rows = -1;
	while (++i.rows < weight->size.rows)
	{
		i.columns = -1;
		while (++i.columns < weight->size.columns)
		{
			((double **)weight->values)[i.rows][i.columns]
				-= 0.01 * ((double **)derivative->weight
					->values)[i.rows][i.columns];
		}
	}
	((double **)weight->values)[0][0] = 0;
	((double **)weight->values)[8][0] = 0;
	return ;
}

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							t_gradient_descent *const gradient_descent)
{
	const t_vector	*predicted;
	const t_vector	*residual;
	t_derivative	*derivative;
	t_vector		*residual_abs;
	double			cost;
	size_t			i;

	if (regression_type == E_LOGISTIC)
	{
		i = 0;
		while (++i <= 50000)
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
			residual_abs = ft_vector_create(sizeof(double),
					residual->size.columns, E_DIR_COLUMN);
			ft_vector_abs_double(residual, residual_abs);
			cost = ft_vector_sum(residual_abs) / residual_abs->size.columns;
			ft_printf("COST: %f\n", cost);
			// ft_vector_print("New weight", gradient_descent->weight, E_DOUBLE);
		}
	}
	return ;
}
