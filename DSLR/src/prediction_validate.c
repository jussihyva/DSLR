/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prediction_validate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:50:19 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/13 14:31:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	prediction_validate(
					const t_matrix *const observed,
					const t_vector *const predicted_argmax)
{
	size_t		i;
	size_t		predicted_value;
	size_t		num_of_right_predictions;

	num_of_right_predictions = 0;
	i = -1;
	while (++i < observed->size.columns)
	{
		predicted_value = ((double **)predicted_argmax->values)[i][0];
		if (((double **)observed->values)[predicted_value][i])
			num_of_right_predictions++;
	}
	ft_printf("Accuracy score: %.2f\n", num_of_right_predictions
		/ (double)observed->size.columns);
	return ;
}
