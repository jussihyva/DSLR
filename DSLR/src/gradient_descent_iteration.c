/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_iteration.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:45:32 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/24 19:01:06 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	cost_influxdb_field_elem_create(
							t_influxdb_line_element *influxdb_line_element,
							const t_vector *const cost,
							const size_t iteration)
{
	char	*string;

	string = ft_strnew(100);
	ft_sprintf(string, "%s=%f,%s=%f,%s=%f,%s=%f,iteration=%lu",
		g_hogwarts_house_array[0], ((double **)cost->values)[0][0],
		g_hogwarts_house_array[1], ((double **)cost->values)[1][0],
		g_hogwarts_house_array[2], ((double **)cost->values)[2][0],
		g_hogwarts_house_array[3], ((double **)cost->values)[3][0],
		iteration);
	influxdb_line_element->string = string;
	influxdb_line_element->string_length = ft_strlen(string);
	return ;
}

static void	cost_send_to_influxdb(
						const t_tcp_connection *const connection,
						const t_dataset *const dataset,
						const t_gradient_descent *const gradient_descent,
						const size_t iteration)
{
	t_bool						result;
	char						*string;
	const char					*influxdb_line;
	t_influxdb_line_element		influxdb_line_element[NUM_INFLUXDB_ELEMENTS];

	string = ft_strnew(1000);
	influxdb_line_measurement_create(&influxdb_line_element[E_MEASUREMENT],
		"dataset_train");
	ft_sprintf(string, "Record_type=cost,iteration=%lu,learning_rate=%f",
		iteration, gradient_descent->hyper_parameters->learning_rate);
	influxdb_line_element[E_TAGS].string = string;
	influxdb_line_element[E_TAGS].string_length = ft_strlen(string);
	cost_influxdb_field_elem_create(&influxdb_line_element[E_FIELDS],
		gradient_descent->cost, iteration);
	influxdb_line_timestamp_create(&influxdb_line_element[E_TIMESTAMP]);
	influxdb_line = elements_merge(influxdb_line_element);
	result = ft_influxdb_write(connection, influxdb_line,
			g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
	if (!result)
		FT_LOG_ERROR("Sending of data to an influxdb failed!");
	ft_strdel((char **)&influxdb_line);
	influxdb_send_weight_and_bias(connection, dataset, gradient_descent,
		iteration);
	return ;
}

void	gradient_descent_iteration(
							const t_dataset *const dataset,
							const t_gradient_descent *const gradient_descent,
							const t_tcp_connection *const connection,
							const t_bool is_influxdb)
{
	t_derivative	*derivative;
	size_t			i;

	derivative = derivative_initialize(gradient_descent->input_values,
			gradient_descent->observed);
	i = 0;
	while (++i <= gradient_descent->hyper_parameters->iterations)
	{
		leayer_calculate(gradient_descent, derivative,
			gradient_descent->hyper_parameters->learning_rate);
		if (!(i % 100) || i == 10 || i == 20 || i == 50)
		{
			if (connection && is_influxdb)
				cost_send_to_influxdb(connection, dataset, gradient_descent, i);
			if (ft_log_get_level() <= LOG_INFO)
				ft_matrix_print("COST", gradient_descent->cost, E_DOUBLE);
		}
	}
	weight_bias_write(gradient_descent->weight, gradient_descent->bias,
		dataset->column_name_array);
	derivative_remove(&derivative);
	return ;
}
