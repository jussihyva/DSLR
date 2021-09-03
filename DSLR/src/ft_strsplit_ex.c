/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:55:33 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/03 15:28:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	ft_save_word(char **array, char *s, int w_len, int w_count)
{
	int		i;

	i = 0;
	array[w_count] = (char *)malloc(sizeof(char) * (w_len + 1));
	while (w_len--)
	{
		array[w_count][i] = *(s - w_len - 1);
		i++;
	}
	array[w_count][i] = '\0';
	return ;
}

static int	ft_count_save(char *s, char c, char **array)
{
	int		w_count;
	int		w_len;

	w_count = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (array)
				array[w_count] = NULL;
			w_count += 1;
			s++;
		}
		else
		{
			w_len = 0;
			while (*s && *s != c)
			{
				w_len++;
				s++;
			}
			if (array)
				ft_save_word(array, s, w_len, w_count);
			w_count += 1;
			if (*s == c)
				s++;
		}
	}
	if (array)
		*(array + w_count) = 0;
	return (w_count);
}

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

char	**ft_strsplit_ex(
					char const *s,
					const char c,
					size_t *const number_of_values)
{
	char		**array;

	array = NULL;
	*number_of_values = count_number_of_values(s, c);
	array = ft_memalloc(sizeof(*array) * (*number_of_values + 1));
	// ft_strsub()
	*number_of_values = ft_count_save((char *)s, c, array);
	return (array);
}
