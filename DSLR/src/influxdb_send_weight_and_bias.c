/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_send_weight_and_bias.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 10:09:32 by juhani            #+#    #+#             */
/*   Updated: 2021/10/24 16:07:08 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void influxdb_send_weight_and_bias(
						const t_tcp_connection *const connection,
						const t_gradient_descent *const gradient_descent,
						const size_t iteration)
{
	t_influxdb_line_element		influxdb_line_element[NUM_INFLUXDB_ELEMENTS];
	char						*string;
	// t_bool						result;
	// const char					*influxdb_line;

	(void)connection;
	influxdb_line_measurement_create(&influxdb_line_element[E_MEASUREMENT],
		"dataset_train");
	string = ft_strnew(1000);
	ft_sprintf(string, "Record_type=weight,iteration=%lu,learning_rate=%f",
		iteration, gradient_descent->hyper_parameters->learning_rate);
	influxdb_line_element[E_TAGS].string = string;
	influxdb_line_element[E_TAGS].string_length = ft_strlen(string);

	// cost_influxdb_field_elem_create(&influxdb_line_element[E_FIELDS],
	// 	gradient_descent->cost, iteration);
	// influxdb_line_timestamp_create(&influxdb_line_element[E_TIMESTAMP]);
	// influxdb_line = elements_merge(influxdb_line_element);
	// result = ft_influxdb_write(connection, influxdb_line,
	// 		g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
	// if (!result)
	// 	FT_LOG_ERROR("Sending of data to an influxdb failed!");
	// ft_strdel((char **)&influxdb_line);
	return ;
}
