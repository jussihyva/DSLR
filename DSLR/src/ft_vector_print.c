/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:26:05 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/17 19:28:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_vector_print(
					const char *const vectior_name,
					const t_vector *const vector,
					const t_content_type content_type)
{
	ft_matrix_print(vectior_name, vector, content_type);
	return ;
}
