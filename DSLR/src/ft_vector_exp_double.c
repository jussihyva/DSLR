/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_exp_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:50:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 07:53:17 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_exp_double(
						t_matrix *vector,
						double value,
						t_matrix *new_vector)
{
	size_t			i;

	i = -1;
	while (++i < vector->size.rows)
		((double **)new_vector->values)[i][0] = exp(value);
	return ;
}
