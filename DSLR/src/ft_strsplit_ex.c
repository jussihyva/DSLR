/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:55:33 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/03 17:56:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_number_of_values(const char *str, const char delim)
{
	size_t	number_of_values;

	number_of_values = 0;
	if (*str)
		number_of_values++;
	while (*str)
	{
		if (*str == delim)
			number_of_values++;
		str++;
	}
	return (number_of_values);
}

static const char	*read_value(
							const char *start_ptr,
							const char *end_ptr)
{
	const char	*value;

	if (start_ptr == end_ptr)
		value = NULL;
	else
		value = ft_strsub(start_ptr, 0, end_ptr - start_ptr);
	return (value);
}

static void	parse_and_save_values(
							const char *const str,
							const char delim,
							const char **value_array)
{
	const char		*start_ptr;
	const char		*end_ptr;
	size_t			i;

	start_ptr = str;
	end_ptr = str;
	i = 0;
	while (*end_ptr)
	{
		if (*end_ptr == delim)
		{
			value_array[i++] = read_value(start_ptr, end_ptr);
			start_ptr = end_ptr + 1;
		}
		end_ptr++;
	}
	if (str != end_ptr)
		value_array[i++] = read_value(start_ptr, end_ptr);
	return ;
}

char	**ft_strsplit_ex(
					const char *const s,
					const char c,
					size_t *const number_of_values)
{
	const char		**value_array;

	*number_of_values = count_number_of_values(s, c);
	value_array = ft_memalloc(sizeof(*value_array) * (*number_of_values + 1));
	parse_and_save_values(s, c, value_array);
	return ((char **)value_array);
}
