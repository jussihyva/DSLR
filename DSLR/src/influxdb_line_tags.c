/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line_tags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:40:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 12:00:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	influxdb_line_tags_create(
							t_influxdb_line_element *tags_element,
							const char *const hogwarts_subject,
							const char *const hogwarts_house)
{
	const char			*string;
	size_t				len;
	t_queue				*queue_str;

	queue_str = ft_queue_init();
	len = 0;
	len += name_value_pair_add("Record_type", "subject", queue_str);
	len += delimiter_add(queue_str, ",");
	string = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_TAGS, hogwarts_subject);
	len += name_value_pair_add("hogwarts_subject", string, queue_str);
	ft_strdel((char **)&string);
	if (*hogwarts_house)
	{
		len += delimiter_add(queue_str, ",");
		string = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_TAGS,
				hogwarts_house);
		len += name_value_pair_add("Hogwarts House", string, queue_str);
		ft_strdel((char **)&string);
	}
	tags_element->string = ft_strcat_queue(queue_str, len);
	ft_queue_remove(&queue_str);
	tags_element->string_length = len;
	return ;
}

void	influxdb_line_tags_create_2(
							t_influxdb_line_element *tags_element,
							const char *const index,
							const char *const hogwarts_house)
{
	static const char	tag_key1[] = "Record_type=index";
	static const char	tag_key2[] = "index";
	static const char	tag_key3[] = "Hogwarts\\ House";
	const char			*string[2];

	string[0] = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_TAGS, index);
	if (*hogwarts_house)
		string[1] = backslash_chars_add(SPECIAL_CHARS_INFLUXDB_TAGS,
				hogwarts_house);
	tags_element->string_length = ft_strlen(tag_key1);
	tags_element->string_length++;
	tags_element->string_length += ft_strlen(tag_key2);
	tags_element->string_length++;
	tags_element->string_length += ft_strlen(string[0]);
	if (*hogwarts_house)
	{
		tags_element->string_length++;
		tags_element->string_length += ft_strlen(tag_key3);
		tags_element->string_length++;
		tags_element->string_length += ft_strlen(string[1]);
		tags_element->string = ft_memalloc(sizeof(*tags_element->string)
				* (tags_element->string_length + 1));
		ft_sprintf(tags_element->string, "%s,%s=%s,%s=%s", tag_key1, tag_key2,
			string[0], tag_key3, string[1]);
		ft_strdel((char **)&string[1]);
	}
	else
	{
		tags_element->string = ft_memalloc(sizeof(*tags_element->string)
				* (tags_element->string_length + 1));
		ft_sprintf(tags_element->string, "%s,%s=%s", tag_key1, tag_key2,
			string[0]);
	}
	ft_strdel((char **)&string[0]);
	return ;
}
