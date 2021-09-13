/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarray_trim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:15:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 12:22:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

void	ft_strarray_trim(const char **const value_array)
{
	const char	*value;
	const char	*new_value;
	const char	**ptr;

	ptr = value_array;
	while (*ptr)
	{
		value = *ptr;
		new_value = ft_strtrim(value);
		ft_strdel((char **)&value);
		*ptr = new_value;
		ptr++;
	}
	return ;
}
