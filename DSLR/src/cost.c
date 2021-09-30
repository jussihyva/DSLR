/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:25:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 12:43:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static t_matrix	*part1_calculate(
						const t_matrix *const observed,
						const t_matrix *const predicted)
{
	t_matrix	*part1;
	t_matrix	*predicted_log;

	part1 = ft_matrix_create(sizeof(double), predicted->size.rows,
			observed->size.columns);
	predicted_log = ft_matrix_create(sizeof(double), predicted->size.rows,
			predicted->size.columns);
	ft_matrix_log(predicted, predicted_log, E_PLUS);
	ft_matrix_multiply_matrix(observed, predicted_log, part1);
	ft_matrix_remove(&predicted_log);
	return (part1);
}

static t_matrix	*part2_calculate(
						const t_matrix *const observed,
						const t_matrix *const predicted)
{
	t_matrix	*part2;
	t_matrix	*predicted_log;
	t_matrix	*observed_subtracted;
	t_matrix	*predicted_subtracted;

	part2 = ft_matrix_create(sizeof(double), predicted->size.rows,
			observed->size.columns);
	predicted_log = ft_matrix_create(sizeof(double), predicted->size.rows,
			predicted->size.columns);
	observed_subtracted = ft_matrix_create(sizeof(double), predicted->size.rows,
			predicted->size.columns);
	predicted_subtracted = ft_matrix_create(sizeof(double),
			predicted->size.rows, predicted->size.columns);
	ft_double_subtract_matrix(1, observed, observed_subtracted);
	ft_double_subtract_matrix(1, predicted, predicted_subtracted);
	ft_matrix_log(predicted_subtracted, predicted_log, E_PLUS);
	ft_matrix_remove(&predicted_subtracted);
	ft_matrix_multiply_matrix(observed_subtracted, predicted_log, part2);
	ft_matrix_remove(&observed_subtracted);
	ft_matrix_remove(&predicted_log);
	return (part2);
}

const t_vector	*cost_recalculate(
				const t_matrix *const predicted,
				const t_matrix *const observed,
				t_vector *const cost)
{
	const t_vector	*loss;
	t_matrix		*cost_matrix;
	t_matrix		*part1;
	t_matrix		*part2;

	part1 = part1_calculate(observed, predicted);
	part2 = part2_calculate(observed, predicted);
	cost_matrix = ft_matrix_create(sizeof(double), predicted->size.rows,
			observed->size.columns);
	ft_matrix_add_matrix(part1, part2, cost_matrix);
	ft_matrix_remove(&part1);
	ft_matrix_remove(&part2);
	loss = ft_matrix_sum(cost_matrix, E_DIR_ROW);
	ft_matrix_remove(&cost_matrix);
	ft_vector_div_double(loss, -(double)predicted->size.columns, cost);
	ft_vector_remove((t_vector **)&loss);
	return (cost);
}
