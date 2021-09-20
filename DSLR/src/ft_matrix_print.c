/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:23:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/20 06:51:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_matrix_print(
					const char *const matrix_name,
					const t_matrix *const matrix,
					const t_content_type content_type)
{
	size_t		i;
	size_t		j;
	size_t		example_cnt;

	example_cnt = 0;
	ft_printf("#example  %s\n", matrix_name);
	i = -1;
	while (++i < matrix->size.rows)
	{
		j = -1;
		while (++j < matrix->size.columns)
		{
			example_cnt++;
			ft_printf("%lu", example_cnt);
			if (content_type == E_INT)
				ft_printf("       %d ", ((int **)matrix->values)[i][j]);
			else if (content_type == E_DOUBLE)
				ft_printf("       %f ", ((double **)matrix->values)[i][j]);
		}
		ft_printf("\n");
	}
	return ;
}
