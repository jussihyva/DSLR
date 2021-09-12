/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 20:18:26 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 00:03:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static size_t	length_calculate(
							const char *special_chars,
							const char *const string)
{
	const char	*ptr;
	size_t		length;

	length = ft_strlen(string);
	ptr = string;
	while (*ptr)
	{
		if (ft_strchr(special_chars, *ptr))
			length++;
		ptr++;
	}
	return (length);
}

static char	*string_create(
							const char *const special_chars,
							const char *const string,
							size_t string_length)
{
	char			*new_string;
	const char		*ptr;
	size_t			i;

	new_string = ft_memalloc(sizeof(*new_string) * (string_length + 1));
	i = 0;
	ptr = string;
	while (*ptr)
	{
		if (ft_strchr(special_chars, *ptr))
			new_string[i++] = '\\';
		new_string[i++] = *ptr;
		ptr++;
	}
	return (new_string);
}

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

void	influxdb_line_tags_create(
							t_influxdb_line_element *tags_element,
							const char *const hogwarts_subject,
							const char *const hogwarts_house)
{
	static const char	tag_key1[] = "hogwarts_subject";
	static const char	tag_key2[] = "Hogwarts\\ House";
	size_t				length[2];
	const char			*string[2];

	length[0] = length_calculate(SPECIAL_CHARS_INFLUXDB_TAGS, hogwarts_subject);
	string[0] = string_create(SPECIAL_CHARS_INFLUXDB_TAGS, hogwarts_subject,
			length[0]);
	length[1] = length_calculate(SPECIAL_CHARS_INFLUXDB_TAGS, hogwarts_house);
	string[1] = string_create(SPECIAL_CHARS_INFLUXDB_TAGS, hogwarts_house,
			length[1]);
	tags_element->string_length = ft_strlen(tag_key1);
	tags_element->string_length++;
	tags_element->string_length += length[0];
	tags_element->string_length++;
	tags_element->string_length += ft_strlen(tag_key2);
	tags_element->string_length++;
	tags_element->string_length += length[1];
	tags_element->string = ft_memalloc(sizeof(*tags_element->string)
			* (tags_element->string_length + 1));
	ft_sprintf(tags_element->string, "%s=%s,%s=%s", tag_key1, string[0],
		tag_key2, string[1]);
	ft_strdel((char **)&string[0]);
	ft_strdel((char **)&string[1]);
	return ;

}

void	influxdb_line_fields_create(
							t_influxdb_line_element *fields_element,
							const char *const value)
{
	static const char	tag_key[] = "value";
	size_t				length;
	char				*string;

	length = length_calculate(SPECIAL_CHARS_INFLUXDB_TAGS, value);
	string = string_create(SPECIAL_CHARS_INFLUXDB_TAGS, value, length);
	fields_element->string_length = ft_strlen(tag_key);
	fields_element->string_length++;
	fields_element->string_length += length;
	fields_element->string = ft_memalloc(sizeof(*fields_element->string)
			* (fields_element->string_length + 1));
	ft_sprintf(fields_element->string, "%s=%s", tag_key, string);
	ft_strdel((char **)&string);
	return ;
}

void	influxdb_line_timestamp_create(
							t_influxdb_line_element *timestamp_element,
							const size_t utc_time_ms)
{
	char		string[100];

	ft_sprintf(string, "%lu", utc_time_ms);
	timestamp_element->string_length = ft_strlen(string);
	timestamp_element->string = ft_strdup(string);
	return ;
}
