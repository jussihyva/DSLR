/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_abs_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 07:19:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/19 07:23:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_abs_double(
						const t_vector *const vector,
						t_vector *const new_vector)
{
	size_t			i;

	i = -1;
	while (++i < vector->size.rows)
		((double **)new_vector->values)[i][0]
			= fabs(((double **)vector->values)[i][0]);
	return ;
}
