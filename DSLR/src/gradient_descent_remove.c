/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_remove.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:17:23 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/29 14:22:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	gradient_descent_remove(
						const t_gradient_descent **const gradient_descent)
{
	ft_matrix_remove(&(*gradient_descent)->bias);
	ft_matrix_remove(&(*gradient_descent)->input_values);
	ft_matrix_remove(&(*gradient_descent)->observed);
	ft_matrix_remove(&(*gradient_descent)->weight);
	ft_memdel((void **)gradient_descent);
	return ;
}
