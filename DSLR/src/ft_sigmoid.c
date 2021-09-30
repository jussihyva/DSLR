/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sigmoid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:26:57 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 13:27:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

const t_matrix	*ft_sigmoid(const t_matrix *const input)
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
