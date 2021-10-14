/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:31:36 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 16:32:55 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	example_remove(void *content, size_t size)
{
	const t_example		*example;

	(void)size;
	example = *(const t_example **)content;
	ft_strarraydel((const char ***)&example->value_array);
	ft_memdel((void **)&example->validity_array);
	ft_memdel((void **)&example->double_value_array);
	ft_memdel((void **)&example);
	return ;
}
