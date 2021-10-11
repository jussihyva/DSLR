/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 12:17:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/11 12:32:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

char	*ft_str_toupper(const char *const str)
{
	char		*new_string;
	size_t		i;

	new_string = ft_strnew(ft_strlen(str));
	i = 0;
	while (str[i])
	{
		new_string[i] = ft_toupper(str[i]);
		i++;
	}
	return (new_string);
}
