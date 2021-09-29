/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 10:31:22 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/29 17:52:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_matrix_remove(t_matrix **matrix)
{
	size_t		i;

	i = -1;
	while (++i < (*matrix)->size.rows)
		ft_memdel(&(*matrix)->values[i]);
	ft_memdel((void **)&(*matrix)->values);
	ft_memdel((void **)matrix);
	return ;
}
