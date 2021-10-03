/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_predict.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:00:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/03 10:15:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	create_result_file(const t_vector *const predicted_argmax)
{
	size_t		i;
	size_t		house_id;

	i = -1;
	while (++i < predicted_argmax->size.rows)
	{
		house_id = (int)((double **)predicted_argmax->values)[i][0];
		ft_printf("%s\n", g_hogwarts_house_array[house_id]);
	}
}

void	gradient_descent_predict(
						t_gradient_descent *const gradient_descent)
{
	const t_matrix		*predicted;
	const t_matrix		*predicted_transposed;
	const t_vector		*predicted_argmax;

	weight_bias_read(&gradient_descent->weight, &gradient_descent->bias);
	ft_matrix_print("BIAS", gradient_descent->bias, E_DOUBLE);
	ft_matrix_print("WEIGHT", gradient_descent->weight, E_DOUBLE);
	predicted = predict(E_LOGISTIC, gradient_descent->input_values,
			gradient_descent->bias, gradient_descent->weight);
	predicted_transposed = ft_matrix_transpose(predicted);
	ft_matrix_print("PREDICTED", predicted_transposed, E_DOUBLE);
	predicted_argmax = ft_matrix_argmax(predicted_transposed, E_DIR_ROW);
	ft_matrix_print("ARGMAX", predicted_argmax, E_DOUBLE);
	create_result_file(predicted_argmax);
	ft_matrix_remove((t_matrix **)&predicted_transposed);
	ft_matrix_remove((t_matrix **)&predicted);
	return ;
}
