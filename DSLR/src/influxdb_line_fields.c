/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line_fields.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:44:45 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/01 16:57:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static size_t	name_value_pair_add(
						const char *const name,
						const char *const value,
						t_queue *const queue_str)
{
	const char			*string;
	size_t				length;

	length = 0;
	string = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_FIELDS,
			name);
	ft_enqueue(queue_str, (void *)string);
	length += ft_strlen(string);
	ft_enqueue(queue_str, ft_strdup("="));
	length++;
	string = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_FIELDS, value);
	ft_enqueue(queue_str, (void *)string);
	length += ft_strlen(string);
	return (length);
}

static size_t	delimiter_add(t_queue *queue)
{
	size_t		length;

	length = 1;
	ft_enqueue(queue, ft_strdup(","));
	return (length);
}

void	influxdb_line_fields_create_2(
							t_influxdb_line_element *const fields_element,
							const char **const column_name_array,
							const char **const value_array)
{
	size_t				i;
	const char			*column_name;
	const char			*value;
	t_queue				*queue_str;

	queue_str = ft_queue_init();
	fields_element->string_length = 0;
	i = 5;
	while (++i < 19)
	{
		column_name = column_name_array[i];
		value = value_array[i];
		if (*value)
		{
			fields_element->string_length += name_value_pair_add(column_name,
					value, queue_str);
			if (i != 18)
				fields_element->string_length += delimiter_add(queue_str);
		}
	}
	fields_element->string = ft_strcat_queue(queue_str,
			fields_element->string_length);
	ft_memdel((void **)&queue_str->in_stack);
	ft_memdel((void **)&queue_str->out_stack);
	ft_memdel((void **)&queue_str);
	return ;
}
