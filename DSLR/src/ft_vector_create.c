/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:30:20 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/16 22:31:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

t_vector	*ft_vector_create(size_t size, size_t length)
{
	static size_t	number_of_rows = 1;
	t_vector		*vector;

	vector = ft_matrix_create(size, number_of_rows, length);
	return (vector);
}
