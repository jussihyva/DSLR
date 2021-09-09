/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_send_to_influxdb.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 00:20:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/09 00:57:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	dataset_send_to_influxdb(
							t_tls_connection *influxdb_connection,
							const t_dataset *const dataset)
{
	time_t		utc_time_ms;
	char		influxdb_field_string[SEND_REC_BUF_MAX_SIZE];
	t_list		*elem;
	const char	**value_array;
	const char	*name;
	double		value;
	size_t		index;
	char		*endptr;

	elem = dataset->value_array_lst;
	while (elem)
	{
		utc_time_ms = ft_gettime();
		value_array = *(const char ***)elem->content;
		index = ft_strtoi(value_array[0], &endptr, 10);
		name = dataset->column_name_array[7];
		value = strtod(value_array[7], &endptr);
		FT_LOG_INFO("%lu %s=%f", index, name, value);
		elem = elem->next;
		ft_sprintf(influxdb_field_string,
			"dataset_train,index=%lu used_percent=%f %ld", index, value, utc_time_ms);
		ft_influxdb_write(influxdb_connection, influxdb_field_string,
			g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
	}
	utc_time_ms = ft_gettime();
	FT_LOG_INFO("Time: %ld", utc_time_ms);
	return ;
}
