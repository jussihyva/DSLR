/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line_subject_based.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:39:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/01 12:46:15 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	subject_related_values(
							t_influxdb_line_element *influxdb_line_element,
							const char **const column_name_array,
							const char **const value_array,
							const size_t i)
{
	const char					*index;
	const char					*hogwarts_house;
	const char					*hogwarts_subject;

	index = value_array[0];
	hogwarts_house = value_array[1];
	hogwarts_subject = column_name_array[i];
	influxdb_line_tags_create(&influxdb_line_element[E_TAGS], hogwarts_subject,
		hogwarts_house);
	influxdb_line_fields_create(&influxdb_line_element[E_FIELDS], index,
		value_array[i]);
	return ;
}

size_t	influxdb_line_subject_based_create(
								const char **const value_array,
								const char **const column_name_array,
								const size_t i,
								t_queue *queue)
{
	const char					*influxdb_line;
	size_t						length;
	t_influxdb_line_element		influxdb_line_element
											[NUMBER_OF_INFLUXDB_LINE_ELEMENTS];

	ft_bzero(influxdb_line_element, sizeof(*influxdb_line_element)
		* NUMBER_OF_INFLUXDB_LINE_ELEMENTS);
	influxdb_line_measurement_create(&influxdb_line_element[E_MEASUREMENT],
		"dataset_train");
	subject_related_values(influxdb_line_element, column_name_array,
		value_array, i);
	influxdb_line_timestamp_create(&influxdb_line_element[E_TIMESTAMP]);
	length = influxdb_line_length_calculate(influxdb_line_element);
	influxdb_line = elements_merge(influxdb_line_element, length);
	ft_enqueue(queue, (void *)influxdb_line);
	return (length + 1);
}
