/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   derivative.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:01:35 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/19 09:42:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	derivative_recalculate_weight(
						const t_matrix *loss,
						const t_matrix *activation_input,
						t_matrix *const weight)
{
	const t_matrix		*activation_input_transposed;
	t_matrix			*weight_prel;

	weight_prel = ft_matrix_create(sizeof(double),
			loss->size.rows, activation_input->size.rows);
	activation_input_transposed = ft_matrix_transpose(activation_input);
	ft_matrix_dot_matrix(loss, activation_input_transposed,
		weight_prel);
	ft_matrix_remove((t_matrix **)&activation_input_transposed);
	ft_matrix_div_double(weight_prel, activation_input->size.columns, weight);
	ft_matrix_remove(&weight_prel);
	return ;
}

void	derivative_recalculate(
							const t_matrix *const activation_input,
							const t_matrix *const observed,
							const t_matrix *const predicted,
							const t_derivative *const derivative)
{
	const t_vector		*bias_prel;
	const t_matrix		*loss;

	loss = loss_calculate(observed, predicted);
	derivative_recalculate_weight(loss, activation_input,
		derivative->weight);
	bias_prel = ft_matrix_sum(loss, E_DIR_ROW);
	ft_matrix_remove((t_matrix **)&loss);
	ft_vector_div_double(bias_prel, activation_input->size.columns,
		derivative->bias);
	ft_matrix_remove((t_matrix **)&bias_prel);
	if (ft_log_get_level() <= LOG_DEBUG)
	{
		ft_matrix_print("derivative WEIGHT", derivative->weight, E_DOUBLE);
		ft_matrix_print("derivative BIAS", derivative->bias, E_DOUBLE);
	}
	return ;
}

t_derivative	*derivative_initialize(
								const t_matrix *const input_values,
								const t_matrix *const observed)
{
	t_derivative	*derivative;
	t_matrix_size	weight_size;
	t_vector_size	bias_size;

	weight_size.rows = observed->size.rows;
	weight_size.columns = input_values->size.rows;
	bias_size.rows = observed->size.rows;
	bias_size.columns = 1;
	derivative = ft_memalloc(sizeof(*derivative));
	derivative->weight = ft_matrix_create(sizeof(double), weight_size.rows,
			weight_size.columns);
	derivative->bias = ft_vector_create(sizeof(double), bias_size.rows,
			E_DIR_ROW);
	return (derivative);
}

void	derivative_remove(t_derivative **derivative)
{
	ft_vector_remove(&(*derivative)->bias);
	ft_matrix_remove(&(*derivative)->weight);
	ft_memdel((void **)derivative);
	return ;
}
