/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_div_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 22:27:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/02 22:30:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_div_double(
					const t_vector *const vector,
					const double value,
					t_vector *const new_vector)
{
	ft_matrix_div_double(vector, value, new_vector);
	return ;
}
