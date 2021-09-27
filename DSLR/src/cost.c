/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 19:25:25 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/27 09:58:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

const t_vector	*cost_calculate(
				const t_matrix *const predicted,
				const t_matrix *const observed)
{
	const t_vector	*cost;
	t_matrix		*cost_matrix;
	t_matrix		*part1;
	t_matrix		*part2;
	t_matrix		*predicted_log;
	t_matrix		*observed_subtracted;
	t_matrix		*predicted_subtracted;

	predicted_log = ft_matrix_create(sizeof(double), predicted->size.rows,
			predicted->size.columns);
	part1 = ft_matrix_create(sizeof(double), predicted->size.rows,
			observed->size.columns);
	part2 = ft_matrix_create(sizeof(double), predicted->size.rows,
			observed->size.columns);
	ft_matrix_log(predicted, predicted_log, E_PLUS);
	ft_matrix_multiply_matrix(observed, predicted_log, part1);
	// ft_matrix_print("Part1", part1, E_DOUBLE);
	observed_subtracted = ft_matrix_create(sizeof(double), predicted->size.rows,
			predicted->size.columns);
	predicted_subtracted = ft_matrix_create(sizeof(double),
			predicted->size.rows, predicted->size.columns);
	ft_double_subtract_matrix(1, observed, observed_subtracted);
	ft_double_subtract_matrix(1, predicted, predicted_subtracted);
	ft_matrix_log(predicted_subtracted, predicted_log, E_PLUS);
	ft_matrix_multiply_matrix(observed_subtracted, predicted_log, part2);
	// ft_matrix_print("Part2", part2, E_DOUBLE);
	cost_matrix = ft_matrix_create(sizeof(double), predicted->size.rows,
			observed->size.columns);
	ft_matrix_add_matrix(part1, part2, cost_matrix);
	cost = ft_matrix_sum(cost_matrix, E_DIR_ROW);
	// ft_matrix_print("cost_matrix", cost_matrix, E_DOUBLE);
	return (cost);
}
