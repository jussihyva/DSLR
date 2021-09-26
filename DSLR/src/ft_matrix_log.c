/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_log.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 22:34:35 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/26 22:35:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_matrix_log(
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
					= log(((double **)matrix->values)[i.rows][i.columns]);
		}
		else
		{
			while (++i.columns < matrix->size.columns)
				((double **)new_matrix->values)[i.rows][i.columns]
					= log(-((double **)matrix->values)[i.rows][i.columns]);
		}
	}
	return ;
}
