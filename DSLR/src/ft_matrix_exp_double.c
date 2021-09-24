/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_exp_double.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:50:49 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/24 14:53:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_matrix_exp_double(
						const t_matrix *const matrix,
						t_matrix *const new_matrix,
						const t_sign sign)
{
	t_vector_size	i;

	i.rows = -1;
	while (++i.rows < matrix->size.rows)
	{
		i.columns = -1;
		if (sign == E_PLUS)
		{
			while (++i.columns < matrix->size.columns)
				((double **)new_matrix->values)[i.rows][i.columns]
					= exp(((double **)matrix->values)[i.rows][i.columns]);
		}
		else
		{
			while (++i.columns < matrix->size.columns)
				((double **)new_matrix->values)[i.rows][i.columns]
					= exp(-((double **)matrix->values)[i.rows][i.columns]);
		}
	}
	return ;
}
