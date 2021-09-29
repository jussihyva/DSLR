/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_remove.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:17:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/29 19:33:11 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	gradient_descent_remove(
						t_gradient_descent **gradient_descent)
{
	ft_vector_remove((t_vector **)&(*gradient_descent)->bias);
	ft_matrix_remove((t_matrix **)&(*gradient_descent)->input_values);
	ft_matrix_remove((t_matrix **)&(*gradient_descent)->observed);
	ft_matrix_remove((t_matrix **)&(*gradient_descent)->weight);
	ft_memdel((void **)gradient_descent);
	return ;
}
