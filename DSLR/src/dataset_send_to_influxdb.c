/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_send_to_influxdb.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 00:20:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 01:03:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

// static void	influxdb_line_format_according_to_rules(char *const influxdb_line)
// {
// 	const char	*line_original;
// 	const char	*ptr;
// 	size_t		i;

// 	line_original = ft_strdup(influxdb_line);
// 	ptr = line_original;
// 	i = 0;
// 	while (*ptr)
// 	{
// 		if (*ptr == ' ')
// 			influxdb_line[i++] = '\\';
// 		influxdb_line[i++] = *ptr;
// 		ptr++;
// 	}
// 	return ;
// }

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

// static const char	*influxdb_line_create(
// 									const char *const hogwarts_house,
// 									const char *const hogwarts_subject,
// 									const char *const value_string)
// {
// 	time_t		utc_time_ms;
// 	char		*endptr;
// 	char		*influxdb_line;
// 	double		value;
// 	const char	*measurement;
// 	char		*tags;
// 	const char	*fields;
// 	char		*timestamp;

// 	if(validate_input(value_string))
// 	{
// 		influxdb_line = ft_memalloc(sizeof(*influxdb_line)
// 				* SEND_REC_BUF_MAX_SIZE);
// 		tags = ft_memalloc(sizeof(*tags) * SEND_REC_BUF_MAX_SIZE);
// 		timestamp = ft_memalloc(sizeof(*timestamp) * SEND_REC_BUF_MAX_SIZE);
// 		value = strtod(value_string, &endptr);
// 		utc_time_ms = ft_gettime();
// 		measurement = ft_strdup("dataset_train");
// 		ft_sprintf(tags, "hogwarts_subject=%s,Hogwarts House=%s",
// 			hogwarts_subject, hogwarts_house);
// 		influxdb_line_format_according_to_rules(tags);
// 		fields = ft_strjoin("value=", value_string);
// 		ft_sprintf(timestamp, "%ld", utc_time_ms);
// 		ft_sprintf(influxdb_line, "%s,%s %s %s", measurement, tags, fields,
// 			timestamp);
// 		ft_strdel((char **)&measurement);
// 		ft_strdel(&tags);
// 		ft_strdel((char **)&fields);
// 		ft_strdel(&timestamp);
// 	}
// 	else
// 		influxdb_line = NULL;
// 	return (influxdb_line);
// }

// static const char	*influxdb_line_create1(
// 									const char *const hogwarts_house,
// 									const t_queue *const field_queue,
// 									const size_t field_string_length_total)
// {
// 	const char	*field_string;
// 	time_t		utc_time_ms;
// 	char		*endptr;
// 	char		*influxdb_line;
// 	double		value;
// 	const char	*measurement;
// 	char		*tags;
// 	const char	*fields;
// 	char		*timestamp;

// 	influxdb_line = NULL;
// 	if (ft_is_queue_empty((t_queue *)field_queue))
// 		fields = NULL;
// 	else
// 	{
// 		fields = ft_memalloc(sizeof(*influxdb_line)
// 				* field_string_length_total);
// 		while (!ft_is_queue_empty((t_queue *)field_queue))
// 		{
// 			field_string = (const char *)ft_dequeue((t_queue *)field_queue);
// 			if (*fields)
// 				ft_strcat(fields, ',');
// 			ft_strcat(fields, field_string);
// 			ft_strdel(&field_string);
// 		}
// 		tags = ft_memalloc(sizeof(*tags) * SEND_REC_BUF_MAX_SIZE);
// 		timestamp = ft_memalloc(sizeof(*timestamp) * SEND_REC_BUF_MAX_SIZE);
// 		value = strtod(value_string, &endptr);
// 		utc_time_ms = ft_gettime();
// 		measurement = ft_strdup("dataset_train");
// 		ft_sprintf(tags, "hogwarts_subject=%s,Hogwarts House=%s",
// 			hogwarts_subject, hogwarts_house);
// 		influxdb_line_format_according_to_rules(tags);
// 		ft_sprintf(timestamp, "%ld", utc_time_ms);
// 		influxdb_line = ft_memalloc(sizeof(*influxdb_line)
// 				* (ft_strlen(measurement) + 1 + ft_strlen(tags) + 1
// 				+ field_string_length_total + 1 + ft_strlen(timestamp)));
// 		ft_sprintf(influxdb_line, "%s,%s %s %s", measurement, tags, fields,
// 			timestamp);
// 		ft_strdel((char **)&measurement);
// 		ft_strdel(&tags);
// 		ft_strdel((char **)&fields);
// 		ft_strdel(&timestamp);
// 	}
// 	return (influxdb_line);
// }

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
	t_list			*elem;
	const char		**value_array;
	size_t			index;
	const char		*hogwarts_subject;
	const char		*hogwarts_house;
	size_t			i;
	t_bool			result;
	t_queue			*field_queue;
	size_t			field_string_length_total;

	(void)result;
	(void)influxdb_connection;
	(void)influxdb_line;
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
		field_string_length_total = 0;
		while (++i < 19)
		{
			hogwarts_subject = dataset->column_name_array[i];
			influxdb_line = influxdb_line_create(hogwarts_house,
					hogwarts_subject, value_array[i], index);
			// if (influxdb_line)
			// {
			// 	ft_enqueue(field_queue, (void *)influxdb_line);
			// 	field_string_length_total += ft_strlen(influxdb_line) + 1;
			// }
			if (influxdb_line)
			{
				result = ft_influxdb_write(influxdb_connection, influxdb_line,
						g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
				if (!result)
					FT_LOG_ERROR("Sending of data to an influxdb failed!");
				ft_strdel((char **)&influxdb_line);
			}
			else
				FT_LOG_WARN("%s %s (check line (dataset file) %lu)",
					"Value is empty for", hogwarts_subject, index);
		}
		// influxdb_line_create1(hogwarts_house, field_queue,
		// 	field_string_length_total);
		elem = elem->next;
	}
	ft_memdel((void **)&field_queue->in_stack);
	ft_memdel((void **)&field_queue->out_stack);
	ft_memdel((void **)&field_queue);
	return ;
}
