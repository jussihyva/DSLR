/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:30:20 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/23 13:36:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

t_vector	*ft_vector_create(
						size_t size,
						size_t length,
						t_vector_type vector_type)
{
	size_t		number_of_rows;
	size_t		number_of_columns;
	t_vector	*vector;

	if (vector_type == E_DIR_COLUMN)
	{
		number_of_rows = 1;
		number_of_columns = length;
	}
	else
	{
		number_of_rows = length;
		number_of_columns = 1;
	}
	vector = ft_matrix_create(size, number_of_rows, number_of_columns);
	return (vector);
}
