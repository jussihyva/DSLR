/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   residual.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 17:24:00 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/19 09:41:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	print_shapes(
				const t_matrix *const predicted_result,
				const t_matrix *const desired_result,
				const t_matrix *const loss)
{
	ft_shape_print("predicted_result", predicted_result);
	ft_shape_print("desired_result", desired_result);
	ft_shape_print("loss", loss);
	return ;
}

const t_matrix	*loss_calculate(
						const t_matrix *const observed,
						const t_matrix *const predicted)
{
	t_matrix	*loss;

	loss = ft_matrix_create(sizeof(double), observed->size.rows,
			observed->size.columns);
	ft_matrix_subtract_matrix(predicted, observed, loss);
	if (ft_log_get_level() <= LOG_DEBUG)
		print_shapes(predicted, observed, loss);
	return (loss);
}
