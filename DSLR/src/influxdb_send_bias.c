/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_send_bias.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:04:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/27 12:38:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	create_tags_elem(
					t_influxdb_line_element *const tags_elem,
					const size_t iteration,
					const double learning_rate)
{
	char						*string;

	string = ft_strnew(1000);
	ft_sprintf(string, "Record_type=bias,iteration=%lu,"
		"learning_rate=%f", iteration, learning_rate);
	tags_elem->string = string;
	tags_elem->string_length = ft_strlen(string);
	return ;
}

static void	create_field_elem(
					t_influxdb_line_element *const field_elem,
					const double **const bias_values)
{
	const char					*house;
	char						*string;
	t_queue						*queue;
	size_t						i;

	queue = ft_queue_init();
	field_elem->string_length = 0;
	i = -1;
	while (++i < NUMBER_OF_HOGWARTS_HOUSES)
	{
		house = g_hogwarts_house_array[i];
		string = ft_strnew(1000);
		ft_sprintf(string, "%f", bias_values[i][0]);
		field_elem->string_length
			+= name_value_pair_add(house, string, queue,
				SPECIAL_CHARS_INFLUXDB_FIELDS);
		ft_strdel(&string);
		if (i < (NUMBER_OF_HOGWARTS_HOUSES - 1))
			field_elem->string_length += delimiter_add(queue, ",");
	}
	field_elem->string = ft_strcat_queue(queue, field_elem->string_length);
	ft_queue_remove(&queue);
	return ;
}

void	influxdb_send_bias(
						const t_tcp_connection *const connection,
						const t_gradient_descent *const gradient_descent,
						const size_t iteration)
{
	t_influxdb_line_element		influxdb_line_element[NUM_INFLUXDB_ELEMENTS];
	t_bool						result;
	const char					*influxdb_line;

	influxdb_line_measurement_create(&influxdb_line_element[E_MEASUREMENT],
		"dataset_train");
	create_tags_elem(&influxdb_line_element[E_TAGS], iteration,
		gradient_descent->hyper_parameters->learning_rate);
	create_field_elem(&influxdb_line_element[E_FIELDS],
		(const double **const)gradient_descent->bias->values);
	influxdb_line_timestamp_create(&influxdb_line_element[E_TIMESTAMP]);
	influxdb_line = elements_merge(influxdb_line_element);
	result = ft_influxdb_write(connection, influxdb_line,
			g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
	if (!result)
		FT_LOG_ERROR("Sending of data to an influxdb failed!");
	ft_strdel((char **)&influxdb_line);
	return ;
}
