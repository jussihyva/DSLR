/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_add_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:14:28 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/24 15:04:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_add_double(
						const t_vector *const vector,
						const double value,
						t_vector *const new_vector)
{
	ft_matrix_add_double(vector, value, new_vector);
	return ;
}
