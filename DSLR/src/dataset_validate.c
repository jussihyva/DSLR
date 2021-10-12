/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:11:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/11 19:53:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

size_t	dataset_validate(const t_dataset *const dataset)
{
	size_t				number_of_valid_examples;
	t_list				*elem;
	const t_example		*example;

	number_of_valid_examples = 0;
	elem = dataset->example_lst;
	while (elem)
	{
		example = *(const t_example **)elem->content;
		elem = elem->next;
	}
	return (number_of_valid_examples);
}
