/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line_group_create.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:51:12 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 14:54:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static size_t	influxdb_line_length_calculate(
								t_influxdb_line_element *influxdb_line_element)
{
	size_t		length;

	length = 0;
	length += influxdb_line_element[E_MEASUREMENT].string_length;
	length++;
	length += influxdb_line_element[E_TAGS].string_length;
	length++;
	length += influxdb_line_element[E_FIELDS].string_length;
	length++;
	length += influxdb_line_element[E_TIMESTAMP].string_length;
	return (length);
}

static const char	*elements_merge(
					t_influxdb_line_element *const influxdb_line_element,
					const size_t length)
{
	char		*influxdb_line;

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
	if (ft_strlen(influxdb_line) != length)
		FT_LOG_WARN("Influxdb line: %lu <--> %lu", ft_strlen(influxdb_line),
			length);
	return (influxdb_line);
}

static const char	*influxdb_line_create(
									const char *const hogwarts_house,
									const char *const hogwarts_subject,
									const char *const value)
{
	const char					*influxdb_line;
	size_t						length;
	t_influxdb_line_element		influxdb_line_element
											[NUMBER_OF_INFLUXDB_LINE_ELEMENTS];

	influxdb_line = NULL;
	ft_bzero(influxdb_line_element, sizeof(*influxdb_line_element)
		* NUMBER_OF_INFLUXDB_LINE_ELEMENTS);
	influxdb_line_measurement_create(&influxdb_line_element[E_MEASUREMENT],
		"dataset_train");
	influxdb_line_tags_create(&influxdb_line_element[E_TAGS],
		hogwarts_subject, hogwarts_house);
	influxdb_line_fields_create(&influxdb_line_element[E_FIELDS], value);
	influxdb_line_timestamp_create(&influxdb_line_element[E_TIMESTAMP],
		ft_gettime());
	length = influxdb_line_length_calculate(influxdb_line_element);
	influxdb_line = elements_merge(influxdb_line_element, length);
	return (influxdb_line);
}

static size_t	influxdb_line_lines_create(
									t_queue *influxdb_line_queue,
									const char **const column_name_array,
									const char **const value_array,
									const char *const hogwarts_house)
{
	size_t			field_string_length_total;
	const char		*influxdb_line;
	size_t			i;
	size_t			index;
	char			*endptr;

	index = ft_strtoi(value_array[0], &endptr, 10);
	if (!(index % 20))
		FT_LOG_INFO("%lu", index);
	i = 5;
	field_string_length_total = -1;
	while (++i < 19)
	{
		if (*value_array[i])
		{
			influxdb_line = influxdb_line_create(hogwarts_house,
					column_name_array[i], value_array[i]);
			ft_enqueue(influxdb_line_queue, (void *)influxdb_line);
			field_string_length_total += ft_strlen(influxdb_line) + 1;
		}
		else
			FT_LOG_DEBUG("%s %s (check line (dataset file) %lu)",
				"Value is empty for", column_name_array[i], index);
	}
	return (field_string_length_total);
}

const char	*influxdb_line_group_create(
					const char *const hogwarts_house,
					const char **const column_name_array,
					const char **const value_array)
{
	char			*influxdb_lines;
	const char		*influxdb_line;
	size_t			field_string_length_total;
	t_queue			*influxdb_line_queue;

	influxdb_line_queue = ft_queue_init();
	field_string_length_total = influxdb_line_lines_create(influxdb_line_queue,
			column_name_array, value_array, hogwarts_house);
	influxdb_lines = ft_strnew(field_string_length_total);
	while (!ft_is_queue_empty(influxdb_line_queue))
	{
		influxdb_line = (const char *)ft_dequeue(influxdb_line_queue);
		if (*influxdb_lines)
			ft_strcat(influxdb_lines, "\n");
		ft_strcat(influxdb_lines, influxdb_line);
		ft_strdel((char **)&influxdb_line);
	}
	ft_memdel((void **)&influxdb_line_queue->in_stack);
	ft_memdel((void **)&influxdb_line_queue->out_stack);
	ft_memdel((void **)&influxdb_line_queue);
	return (influxdb_lines);
}
