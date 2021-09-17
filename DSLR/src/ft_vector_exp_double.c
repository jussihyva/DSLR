/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_exp_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:50:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 19:35:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_exp_double(
						const t_matrix *const vector,
						t_matrix *const new_vector)
{
	size_t			i;

	i = -1;
	while (++i < vector->size.rows)
		((double **)new_vector->values)[i][0]
			= exp(-((double **)vector->values)[i][0]);
	return ;
}
