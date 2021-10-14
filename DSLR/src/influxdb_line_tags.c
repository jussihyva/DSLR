/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_line_tags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:40:40 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 14:05:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	influxdb_line_tags_create(
							t_influxdb_line_element *tags_element,
							const char *const hogwarts_subject,
							const char *const hogwarts_house)
{
	size_t				len;
	t_queue				*queue_str;

	queue_str = ft_queue_init();
	len = 0;
	len += name_value_pair_add("Record_type", "subject", queue_str,
			SPECIAL_CHARS_INFLUXDB_TAGS);
	len += delimiter_add(queue_str, ",");
	len += name_value_pair_add("hogwarts_subject", hogwarts_subject, queue_str,
			SPECIAL_CHARS_INFLUXDB_TAGS);
	if (*hogwarts_house)
	{
		len += delimiter_add(queue_str, ",");
		len += name_value_pair_add("Hogwarts House", hogwarts_house, queue_str,
				SPECIAL_CHARS_INFLUXDB_TAGS);
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
	size_t				len;
	t_queue				*queue_str;

	queue_str = ft_queue_init();
	len = 0;
	len += name_value_pair_add("Record_type", "index", queue_str,
			SPECIAL_CHARS_INFLUXDB_TAGS);
	len += delimiter_add(queue_str, ",");
	len += name_value_pair_add("index", index, queue_str,
			SPECIAL_CHARS_INFLUXDB_TAGS);
	if (*hogwarts_house)
	{
		len += delimiter_add(queue_str, ",");
		len += name_value_pair_add("Hogwarts House", hogwarts_house, queue_str,
				SPECIAL_CHARS_INFLUXDB_TAGS);
	}
	tags_element->string = ft_strcat_queue(queue_str, len);
	ft_queue_remove(&queue_str);
	tags_element->string_length = len;
	return ;
}
