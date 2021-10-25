/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_send_bias.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:04:18 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/25 12:15:10 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	create_tags_elem(
					t_influxdb_line_element *const tags_elem,
					const char *const house,
					const size_t iteration,
					const double learning_rate)
{
	char						*string;

	string = ft_strnew(1000);
	ft_sprintf(string, "Record_type=bias,iteration=%lu,"
		"learning_rate=%f,house=%s", iteration, learning_rate, house);
	tags_elem->string = string;
	tags_elem->string_length = ft_strlen(string);
	return ;
}

static void	create_field_elem(
					t_influxdb_line_element *const field_elem,
					const double bias_value)
{
	const char					*column_name;
	char						*string;
	t_queue						*queue;

	queue = ft_queue_init();
	field_elem->string_length = 0;
	column_name = ft_strdup("value");
	string = ft_strnew(1000);
	ft_sprintf(string, "%f", bias_value);
	field_elem->string_length
		+= name_value_pair_add(column_name, string, queue,
			SPECIAL_CHARS_INFLUXDB_FIELDS);
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
	size_t						i;
	t_bool						result;
	const char					*influxdb_line;

	i = -1;
	while (++i < NUMBER_OF_HOGWARTS_HOUSES)
	{
		influxdb_line_measurement_create(&influxdb_line_element[E_MEASUREMENT],
			"dataset_train");
		create_tags_elem(&influxdb_line_element[E_TAGS],
			g_hogwarts_house_array[i], iteration,
			gradient_descent->hyper_parameters->learning_rate);
		create_field_elem(&influxdb_line_element[E_FIELDS],
			((double **)gradient_descent->bias->values)[i][0]);
		influxdb_line_timestamp_create(&influxdb_line_element[E_TIMESTAMP]);
		influxdb_line = elements_merge(influxdb_line_element);
		result = ft_influxdb_write(connection, influxdb_line,
				g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
		if (!result)
			FT_LOG_ERROR("Sending of data to an influxdb failed!");
		ft_strdel((char **)&influxdb_line);
	}
	return ;
}
