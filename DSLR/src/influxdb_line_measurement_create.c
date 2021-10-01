/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line_measurement_create.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:29:15 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/01 10:54:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	influxdb_line_measurement_create(
								t_influxdb_line_element *measurement_element,
								const char *const measurement)
{
	measurement_element->string
		= backslash_chars_add(SPECIAL_CHARS_INFLUXDB_MEASUREMENT, measurement);
	measurement_element->string_length = ft_strlen(measurement_element->string);
	return ;
}
