/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:02:13 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/12 12:33:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

const t_dataset_stat	*dataset_stat_initialize(const size_t number_of_columns)
{
	t_dataset_stat	*stat;

	stat = ft_memalloc(sizeof(*stat));
	stat->sum_array = ft_memalloc(sizeof(*stat->sum_array) * number_of_columns);
	stat->num_of_values_array = ft_memalloc(sizeof(*stat->num_of_values_array)
			* number_of_columns);
	stat->mean_array = ft_memalloc(sizeof(*stat->mean_array)
			* number_of_columns);
	return (stat);
}

void	dataaset_stat_remove(t_dataset_stat **stat)
{
	ft_memdel((void **)&(*stat)->mean_array);
	ft_memdel((void **)&(*stat)->num_of_values_array);
	ft_memdel((void **)&(*stat)->sum_array);
	ft_memdel((void **)stat);
}
