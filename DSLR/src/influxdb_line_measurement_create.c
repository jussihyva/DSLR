/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line_measurement_create.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:29:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 12:30:06 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	influxdb_line_measurement_create(
								t_influxdb_line_element *measurement_element,
								const char *const measurement)
{
	measurement_element->string_length
		= length_calculate(SPECIAL_CHARS_INFLUXDB_MEASUREMENT, measurement);
	measurement_element->string
		= string_create(SPECIAL_CHARS_INFLUXDB_MEASUREMENT, measurement,
			measurement_element->string_length);
	return ;
}
