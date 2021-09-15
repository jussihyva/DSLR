/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_send_to_influxdb.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 00:20:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/15 18:40:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	dataset_send_to_influxdb(
							const t_tcp_connection *const influxdb_connection,
							const t_dataset *const dataset)
{
	const char		*influxdb_lines;
	t_list			*elem;
	const char		**value_array;
	t_bool			result;

	elem = dataset->value_array_lst;
	while (elem)
	{
		value_array = *(const char ***)elem->content;
		influxdb_lines = influxdb_line_group_create(dataset->column_name_array,
				value_array);
		if (influxdb_lines)
		{
			result = ft_influxdb_write(influxdb_connection, influxdb_lines,
					g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
			if (!result)
				FT_LOG_ERROR("Sending of data to an influxdb failed!");
			ft_strdel((char **)&influxdb_lines);
		}
		elem = elem->next;
	}
	return ;
}
