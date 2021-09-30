/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 10:14:54 by jkauppi          ###   ########.fr       */
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
	ft_matrix_remove(&predicted_exp);
	ft_double_div_vector(1, predicted_add, predicted_div);
	ft_matrix_remove(&predicted_add);
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

static t_derivative	*derivative_calculate(
									const t_matrix *const activation_input,
									const t_vector *const residual)
{
	const t_vector		*activation_input_transposed;
	t_matrix			*weight_prel;
	const t_vector		*bias_prel;
	t_derivative		*derivative;

	activation_input_transposed = ft_vector_transpose(activation_input);
	derivative = ft_memalloc(sizeof(*derivative));
	weight_prel = ft_matrix_create(sizeof(double),
			residual->size.rows, activation_input->size.rows);
	derivative->weight = ft_matrix_create(sizeof(double),
			residual->size.rows, activation_input->size.rows);
	derivative->bias = ft_vector_create(sizeof(double), residual->size.rows,
			E_DIR_ROW);
	ft_matrix_dot_matrix(residual, activation_input_transposed,
		weight_prel);
	ft_vector_remove((t_vector **)&activation_input_transposed);
	ft_vector_div_double(weight_prel, activation_input->size.columns,
		derivative->weight);
	ft_vector_remove(&weight_prel);
	bias_prel = ft_matrix_sum(residual, E_DIR_ROW);
	ft_vector_div_double(bias_prel, activation_input->size.columns,
		derivative->bias);
	ft_matrix_remove((t_matrix **)&bias_prel);
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

void	gradient_descent_iteration(
							const t_regression_type regression_type,
							const t_gradient_descent *const gradient_descent)
{
	const t_matrix	*predicted;
	const t_matrix	*residual;
	t_derivative	*derivative;
	const t_vector	*cost;
	size_t			i;

	if (regression_type == E_LOGISTIC)
	{
		i = 0;
		while (++i <= ITERATION_LOOP)
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
			ft_vector_remove(&derivative->bias);
			ft_matrix_remove(&derivative->weight);
			ft_memdel((void **)&derivative);
			cost = cost_calculate(predicted, gradient_descent->observed);
			ft_matrix_remove((t_matrix **)&predicted);
			if (ft_log_get_level() <= LOG_INFO)
				ft_matrix_print("COST", cost, E_DOUBLE);
			ft_matrix_remove((t_matrix **)&residual);
			ft_vector_remove((t_vector **)&cost);
		}
	}
	weight_bias_save(gradient_descent->weight, gradient_descent->bias);
	return ;
}
