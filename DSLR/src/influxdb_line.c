/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 20:18:26 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/01 15:45:37 by jkauppi          ###   ########.fr       */
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

char	*backslash_chars_add(
					const char *const special_chars,
					const char *const string)
{
	char			*new_string;
	const char		*ptr;
	size_t			new_length;
	size_t			i;

	new_length = length_calculate(SPECIAL_CHARS_INFLUXDB_TAGS, string);
	new_string = ft_strnew(new_length);
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

void	influxdb_line_fields_create(
							t_influxdb_line_element *fields_element,
							const char *const index,
							const char *const value)
{
	static const char	tag_key1[] = "Index";
	static const char	tag_key2[] = "value";
	char				*string;

	string = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_FIELDS, value);
	fields_element->string_length = 0;
	fields_element->string_length += ft_strlen(tag_key1);
	fields_element->string_length++;
	fields_element->string_length += ft_strlen(index);
	fields_element->string_length++;
	fields_element->string_length += ft_strlen(tag_key2);
	fields_element->string_length++;
	fields_element->string_length += ft_strlen(string);
	fields_element->string = ft_memalloc(sizeof(*fields_element->string)
			* (fields_element->string_length + 1));
	ft_sprintf(fields_element->string, "%s=%s,%s=%s", tag_key1, index, tag_key2,
		string);
	ft_strdel((char **)&string);
	return ;
}

void	influxdb_line_timestamp_create(
							t_influxdb_line_element *timestamp_element)
{
	size_t		utc_time_ms;
	char		string[100];

	utc_time_ms = ft_gettime();
	ft_sprintf(string, "%lu", utc_time_ms);
	timestamp_element->string_length = ft_strlen(string);
	timestamp_element->string = ft_strdup(string);
	return ;
}
