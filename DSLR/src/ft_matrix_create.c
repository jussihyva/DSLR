/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:28:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/16 22:31:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

t_matrix	*ft_matrix_create(
						size_t size,
						const size_t number_fo_rows,
						const size_t number_of_columns)
{
	t_matrix		*matrix;
	size_t			i;

	matrix = ft_memalloc(sizeof(*matrix));
	matrix->values = (void **)ft_memalloc(sizeof(*matrix->values)
			* number_fo_rows);
	i = -1;
	while (++i < number_fo_rows)
		matrix->values[i] = (void *)ft_memalloc(size * number_of_columns);
	matrix->size.rows = number_fo_rows;
	matrix->size.columns = number_of_columns;
	return (matrix);
}
