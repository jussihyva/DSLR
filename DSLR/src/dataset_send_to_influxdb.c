/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset_send_to_influxdb.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 00:20:24 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/11 14:34:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	influxdb_line_format_according_to_rules(char *const influxdb_line)
{
	const char	*line_original;
	const char	*ptr;
	size_t		i;

	line_original = ft_strdup(influxdb_line);
	ptr = line_original;
	i = 0;
	while (*ptr)
	{
		if (ft_isspace(*ptr))
			influxdb_line[i++] = '\\';
		influxdb_line[i++] = *ptr;
		ptr++;
	}
	return ;
}

static t_bool	validate_input(const char *const value_string)
{
	t_bool		result;
	const char	*ptr;

	result = E_FALSE;
	ptr = value_string;
	while (*ptr && ft_isspace(*ptr))
		ptr++;
	if (*ptr)
		result = E_TRUE;
	return (result);
}

static const char	*influxdb_line_create(
									const char *const hogwarts_house,
									const char *const hogwarts_subject,
									const char *const value_string)
{
	time_t		utc_time_ms;
	char		*endptr;
	char		*influxdb_line;
	double		value;
	const char	*measurement;
	char		*tags;
	const char	*fields;
	char		*timestamp;

	if(validate_input(value_string))
	{
		influxdb_line = ft_memalloc(sizeof(*influxdb_line)
				* SEND_REC_BUF_MAX_SIZE);
		tags = ft_memalloc(sizeof(*tags) * SEND_REC_BUF_MAX_SIZE);
		timestamp = ft_memalloc(sizeof(*timestamp) * SEND_REC_BUF_MAX_SIZE);
		value = strtod(value_string, &endptr);
		utc_time_ms = ft_gettime();
		measurement = ft_strdup("dataset_train");
		ft_sprintf(tags, "hogwarts_subject=%s,Hogwarts House=%s",
			hogwarts_subject, hogwarts_house);
		influxdb_line_format_according_to_rules(tags);
		fields = ft_strjoin("value=", value_string);
		ft_sprintf(timestamp, "%ld", utc_time_ms);
		ft_sprintf(influxdb_line, "%s,%s %s %s", measurement, tags, fields,
			timestamp);
		ft_strdel((char **)&measurement);
		ft_strdel(&tags);
		ft_strdel((char **)&fields);
		ft_strdel(&timestamp);
	}
	else
		influxdb_line = NULL;
	return (influxdb_line);
}

void	dataset_send_to_influxdb(
							t_tcp_connection *influxdb_connection,
							const t_dataset *const dataset)
{
	char		*endptr;
	const char	*influxdb_line;
	t_list		*elem;
	const char	**value_array;
	size_t		index;
	const char	*hogwarts_subject;
	const char	*hogwarts_house;
	size_t		i;
	t_bool		result;

	elem = dataset->value_array_lst;
	while (elem)
	{
		value_array = *(const char ***)elem->content;
		index = ft_strtoi(value_array[0], &endptr, 10);
		hogwarts_house = value_array[1];
		if (!(index % 20))
			FT_LOG_INFO("%lu", index);
		i = 5;
		while (++i < 19)
		{
			hogwarts_subject = dataset->column_name_array[i];
			influxdb_line = influxdb_line_create(hogwarts_house,
					hogwarts_subject, value_array[i]);
			if (influxdb_line)
			{
				result = ft_influxdb_write(influxdb_connection, influxdb_line,
						g_influxdb_token_array, NUMBER_OF_INFLUXDB_TOKENS);
				if (!result)
					FT_LOG_ERROR("Sending of data to an influxdb failed!");
				ft_strdel((char **)&influxdb_line);
			}
			else
				FT_LOG_WARN("Value is empty for %s (check line %lu)",
					hogwarts_subject, index);
		}
		elem = elem->next;
	}
	return ;
}
