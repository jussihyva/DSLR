/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_send_to_influxdb.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 00:20:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 01:30:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static t_bool	validate_input(const char *const value_string)
{
	t_bool		result;
	const char	*ptr;

	result = E_FALSE;
	ptr = value_string;
	while (*ptr && ft_isspace(*ptr))
		ptr++;
	if (*ptr)
		result = E_TRUE;
	return (result);
}

static const char	*influxdb_line_create(
									const char *const hogwarts_house,
									const char *const hogwarts_subject,
									const char *const value,
									const size_t index)
{
	char						*influxdb_line;
	size_t						length;
	t_influxdb_line_element		influxdb_line_element
											[NUMBER_OF_INFLUXDB_LINE_ELEMENTS];

	if (validate_input(value))
	{
		ft_bzero(influxdb_line_element, sizeof(*influxdb_line_element)
			* NUMBER_OF_INFLUXDB_LINE_ELEMENTS);
		influxdb_line_measurement_create(&influxdb_line_element[E_MEASUREMENT],
			"dataset_train");
		influxdb_line_tags_create(&influxdb_line_element[E_TAGS],
			hogwarts_subject, hogwarts_house);
		influxdb_line_fields_create(&influxdb_line_element[E_FIELDS], value);
		influxdb_line_timestamp_create(&influxdb_line_element[E_TIMESTAMP],
			ft_gettime());
		length = influxdb_line_element[E_MEASUREMENT].string_length;
		length++;
		length += influxdb_line_element[E_TAGS].string_length;
		length++;
		length += influxdb_line_element[E_FIELDS].string_length;
		length++;
		length += influxdb_line_element[E_TIMESTAMP].string_length;
		FT_LOG_WARN("LENGTH=%lu", length);
		influxdb_line = ft_strnew(sizeof(*influxdb_line) * length);
		ft_sprintf(influxdb_line, "%s,%s %s %s",
			influxdb_line_element[E_MEASUREMENT].string,
			influxdb_line_element[E_TAGS].string,
			influxdb_line_element[E_FIELDS].string,
			influxdb_line_element[E_TIMESTAMP].string);
		ft_strdel(&influxdb_line_element[E_MEASUREMENT].string);
		ft_strdel(&influxdb_line_element[E_TAGS].string);
		ft_strdel(&influxdb_line_element[E_FIELDS].string);
		ft_strdel(&influxdb_line_element[E_TIMESTAMP].string);
		FT_LOG_WARN("Influxdb line: %s", influxdb_line);
	}
	else
	{
		influxdb_line = NULL;
		FT_LOG_WARN("%s %s (check line (dataset file) %lu)",
			"Value is empty for", hogwarts_subject, index);
	}
	return (influxdb_line);
}

void	dataset_send_to_influxdb(
							t_tcp_connection *influxdb_connection,
							const t_dataset *const dataset)
{
	char			*endptr;
	const char		*influxdb_line;
	char			*influxdb_lines;
	t_list			*elem;
	const char		**value_array;
	size_t			index;
	const char		*hogwarts_subject;
	const char		*hogwarts_house;
	size_t			i;
	t_bool			result;
	t_queue			*field_queue;
	size_t			field_string_length_total;

	field_queue = ft_queue_init();
	elem = dataset->value_array_lst;
	while (elem)
	{
		value_array = *(const char ***)elem->content;
		index = ft_strtoi(value_array[0], &endptr, 10);
		hogwarts_house = value_array[1];
		if (!(index % 20))
			FT_LOG_INFO("%lu", index);
		i = 5;
		field_string_length_total = -1;
		while (++i < 19)
		{
			hogwarts_subject = dataset->column_name_array[i];
			influxdb_line = influxdb_line_create(hogwarts_house,
					hogwarts_subject, value_array[i], index);
			if (influxdb_line)
			{
				ft_enqueue(field_queue, (void *)influxdb_line);
				field_string_length_total += ft_strlen(influxdb_line) + 1;
			}
		}
		influxdb_lines = ft_strnew(field_string_length_total);
		while (!ft_is_queue_empty(field_queue))
		{
			influxdb_line = (const char *)ft_dequeue(field_queue);
			if (*influxdb_lines)
				ft_strcat(influxdb_lines, "\n");
			ft_strcat(influxdb_lines, influxdb_line);
			ft_strdel((char **)&influxdb_line);
		}
		if (influxdb_lines)
		{
			result = ft_influxdb_write(influxdb_connection, influxdb_lines,
					g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
			if (!result)
				FT_LOG_ERROR("Sending of data to an influxdb failed!");
			ft_strdel((char **)&influxdb_lines);
		}
		else
			FT_LOG_WARN("%s %s (check line (dataset file) %lu)",
				"Value is empty for", hogwarts_subject, index);
		elem = elem->next;
	}
	ft_memdel((void **)&field_queue->in_stack);
	ft_memdel((void **)&field_queue->out_stack);
	ft_memdel((void **)&field_queue);
	return ;
}
