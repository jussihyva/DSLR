/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   derivative.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:01:35 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 13:34:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	derivative_recalculate(
							const t_matrix *const activation_input,
							const t_matrix *const observed,
							const t_matrix *const predicted,
							const t_derivative *const derivative)
{
	const t_vector		*activation_input_transposed;
	t_matrix			*weight_prel;
	const t_vector		*bias_prel;
	const t_matrix		*residual;

	residual = residual_calculate(observed, predicted);
	activation_input_transposed = ft_vector_transpose(activation_input);
	weight_prel = ft_matrix_create(sizeof(double),
			residual->size.rows, activation_input->size.rows);
	ft_matrix_dot_matrix(residual, activation_input_transposed,
		weight_prel);
	ft_vector_remove((t_vector **)&activation_input_transposed);
	ft_vector_div_double(weight_prel, activation_input->size.columns,
		derivative->weight);
	ft_vector_remove(&weight_prel);
	bias_prel = ft_matrix_sum(residual, E_DIR_ROW);
	ft_matrix_remove((t_matrix **)&residual);
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
								const t_matrix_size *const weight_size,
								const t_matrix_size *const bias_size)
{
	t_derivative	*derivative;

	derivative = ft_memalloc(sizeof(*derivative));
	derivative->weight = ft_matrix_create(sizeof(double), weight_size->rows,
			weight_size->columns);
	derivative->bias = ft_vector_create(sizeof(double), bias_size->rows,
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
