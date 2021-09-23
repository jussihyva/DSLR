/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/23 17:02:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_vector	*ft_sigmoid(const t_vector *const input)
{
	t_vector	*predicted_exp;
	t_vector	*predicted_add;
	t_vector	*predicted_div;

	predicted_exp = ft_vector_create(sizeof(double), input->size.columns,
			E_DIR_COLUMN);
	predicted_add = ft_vector_create(sizeof(double), input->size.columns,
			E_DIR_COLUMN);
	predicted_div = ft_vector_create(sizeof(double), input->size.columns,
			E_DIR_COLUMN);
	ft_vector_exp_double(input, predicted_exp, E_MINUS);
	ft_vector_add_double(predicted_exp, 1, predicted_add);
	ft_double_div_vector(1, predicted_add, predicted_div);
	// ft_vector_print("Input vector", input_vector, E_DOUBLE);
	// ft_vector_print("Sigmod vector", predicted_div, E_DOUBLE);
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
							const double bias,
							const t_vector *const weight)
{
	t_vector			*predicted_prel;
	t_vector			*predicted_add;
	const t_vector		*weight_transposed;
	const t_vector		*predicted;

	predicted_prel = ft_vector_create(sizeof(double), matrix->size.columns,
			E_DIR_COLUMN);
	predicted_add = ft_vector_create(sizeof(double), matrix->size.columns,
			E_DIR_COLUMN);
	predicted = ft_vector_create(sizeof(double), matrix->size.columns,
			E_DIR_COLUMN);
	if (regression_type == E_LOGISTIC)
	{
		weight_transposed = ft_vector_transpose(weight);
		ft_vector_dot_matrix_double(weight_transposed, matrix, predicted_prel);
		ft_vector_add_double(predicted_prel, bias, predicted_add);
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
							double *bias)
{
	t_vector_size	i;

	*bias += 0.01 * derivative->bias;
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
				&gradient_descent->bias);
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
