/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:07:54 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 11:20:34 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	ft_queue_remove(t_queue **queue)
{
	ft_memdel((void **)&(*queue)->in_stack);
	ft_memdel((void **)&(*queue)->out_stack);
	ft_memdel((void **)queue);
	return ;
}
