/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_exp_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:50:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 11:16:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_exp_double(
						const t_vector *const vector,
						t_vector *const new_vector,
						const t_sign sign)
{
	t_vector_size	i;

	i.rows = -1;
	while (++i.rows < vector->size.rows)
	{
		i.columns = -1;
		if (sign == E_PLUS)
		{
			while (++i.columns < vector->size.columns)
				((double **)new_vector->values)[i.rows][i.columns]
					= exp(((double **)vector->values)[i.rows][i.columns]);
		}
		else
		{
			while (++i.columns < vector->size.columns)
				((double **)new_vector->values)[i.rows][i.columns]
					= exp(-((double **)vector->values)[i.rows][i.columns]);
		}
	}
	return ;
}
