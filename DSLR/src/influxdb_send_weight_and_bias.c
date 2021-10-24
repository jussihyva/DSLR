/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_send_weight_and_bias.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:09:32 by juhani            #+#    #+#             */
/*   Updated: 2021/10/24 20:56:34 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void influxdb_send_weight_and_bias(
						const t_tcp_connection *const connection,
						const t_dataset *const dataset,
						const t_gradient_descent *const gradient_descent,
						const size_t iteration)
{
	t_influxdb_line_element		influxdb_line_element[NUM_INFLUXDB_ELEMENTS];
	char						*string;
	size_t						i;
	size_t						j;
	size_t						column;
	const char					*column_name;
	double						value;
	t_queue						*queue;
	t_bool						result;
	const char					*influxdb_line;

	queue = ft_queue_init();
	j = -1;
	while (++j < NUMBER_OF_HOGWARTS_HOUSES)
	{
		influxdb_line_measurement_create(&influxdb_line_element[E_MEASUREMENT],
			"dataset_train");
		string = ft_strnew(1000);
		ft_sprintf(string, "Record_type=weight,iteration=%lu,"
			"learning_rate=%f,house=%s", iteration,
			gradient_descent->hyper_parameters->learning_rate,
			g_hogwarts_house_array[j]);
		influxdb_line_element[E_TAGS].string = string;
		influxdb_line_element[E_TAGS].string_length = ft_strlen(string);
		influxdb_line_element[E_FIELDS].string_length = 0;
		i = -1;
		while (++i < NUMBER_OF_INPUT_FUNCTIONS)
		{
			column = g_function_columns[i];
			column_name = dataset->column_name_array[column];
			value = ((double **)gradient_descent->weight->values)[j][i];
			string = ft_strnew(1000);
			ft_sprintf(string, "%f", value);
			influxdb_line_element[E_FIELDS].string_length
				+= name_value_pair_add(column_name, string, queue,
					SPECIAL_CHARS_INFLUXDB_FIELDS);
			if (i < (NUMBER_OF_INPUT_FUNCTIONS - 1))
				influxdb_line_element[E_FIELDS].string_length
					+= delimiter_add(queue, ",");
		}
		influxdb_line_element[E_FIELDS].string = ft_strcat_queue(queue,
				influxdb_line_element[E_FIELDS].string_length);
		influxdb_line_timestamp_create(&influxdb_line_element[E_TIMESTAMP]);
		influxdb_line = elements_merge(influxdb_line_element);
		result = ft_influxdb_write(connection, influxdb_line,
				g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
		if (!result)
			FT_LOG_ERROR("Sending of data to an influxdb failed!");
		ft_strdel((char **)&influxdb_line);
	}
	ft_queue_remove(&queue);
	return ;
}
