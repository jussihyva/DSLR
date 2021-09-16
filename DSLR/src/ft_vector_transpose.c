/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_transpose.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 23:56:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 00:25:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

t_vector	*ft_vector_transpose(const t_vector *const vector)
{
	t_vector	*new_vector;

	new_vector = (t_vector *)ft_matrix_transpose(vector);
	return (new_vector);
}
