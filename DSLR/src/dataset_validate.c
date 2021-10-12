/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:11:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/12 13:09:05 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	statistics_update(
						const t_dataset_stat *const stat,
						const double value,
						size_t i)
{
	stat->sum_array[i] += value;
	stat->num_of_values_array[i]++;
	return ;
}

void	example_validate_and_statistics_update(
					t_example *const example,
					const size_t number_of_values,
					const t_dataset_stat *stat)
{
	size_t		i;
	char		*endptr;
	double		value;

	example->are_all_values_valid = E_TRUE;
	example->validity_array = ft_memalloc(sizeof(*example->validity_array)
			* number_of_values);
	example->double_value_array
		= ft_memalloc(sizeof(*example->double_value_array)
			* number_of_values);
	i = -1;
	while (++i < number_of_values)
	{
		errno = 0;
		value = strtod(example->value_array[i], &endptr);
		if (errno == 0 && *endptr == '\0')
		{
			example->double_value_array[i] = value;
			example->validity_array[i] = E_TRUE;
			statistics_update(stat, value, i);
		}
		else
			example->are_all_values_valid = E_FALSE;
	}
	return ;
}
