/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:06:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/13 00:59:43 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	array_print(
					const char **const array,
					const size_t number_of_values)
{
	size_t		i;

	i = -1;
	while (++i < number_of_values)
		FT_LOG_TRACE("  %s", array[i]);
	return ;
}

static void	create_column_arrays(
						const char *const line,
						t_dataset *const dataset)
{
	const char		*column_name;
	size_t			i;

	dataset->column_name_array = (const char **)ft_strsplit_ex(line, ',',
			&dataset->number_of_columns);
	dataset->column_length_array
		= ft_memalloc(sizeof(*dataset->column_length_array)
			* (dataset->number_of_columns + 1));
	FT_LOG_INFO("%s", line);
	FT_LOG_INFO("Columns:");
	i = -1;
	while (++i < dataset->number_of_columns)
	{
		column_name = dataset->column_name_array[i];
		FT_LOG_INFO("  %s", column_name);
		if (column_name)
			dataset->column_length_array[i] = ft_strlen(column_name);
	}
	FT_LOG_INFO("Number of columns: %d", dataset->number_of_columns);
	return ;
}

static void	trim_values(
					const char **value_array)
{
	const char	*value;
	const char	*new_value;

	while (*value_array)
	{
		value = *value_array;
		new_value = ft_strtrim(value);
		ft_strdel((char **)&value);
		*value_array = new_value;
		value_array++;
	}
	return ;
}

static void	dataset_save_record(
							const char *const line,
							t_list **const value_array_lst,
							const size_t number_of_columns)
{
	size_t			number_of_values;
	const char		**value_array;
	const t_list	*new_elem;

	value_array = (const char **)ft_strsplit_ex(line, ',', &number_of_values);
	trim_values(value_array);
	if (number_of_values != number_of_columns)
	{
		array_print(value_array, number_of_values);
		ft_printf("%s\n", line);
		FT_LOG_FATAL("FATAL: %u\n", number_of_values);
	}
	new_elem = ft_lstnew(&value_array, sizeof(value_array));
	ft_lstadd(value_array_lst, (t_list *)new_elem);
	FT_LOG_DEBUG("%s\n", line);
	array_print(value_array, number_of_columns);
	return ;
}

static const t_dataset	*dataset_read_file(
								const char *const file_path)
{
	t_dataset		*dataset;
	t_file_params	file_params;
	size_t			line_cnt;

	dataset = ft_memalloc(sizeof(*dataset));
	dataset->file_path = file_path;
	file_params.fd = ft_open_fd(file_path);
	file_params.line = NULL;
	line_cnt = 0;
	while (ft_get_next_line(file_params.fd, &file_params.line) > 0)
	{
		line_cnt++;
		if (line_cnt == 1)
			create_column_arrays(file_params.line, dataset);
		else
			dataset_save_record(file_params.line, &dataset->value_array_lst,
				dataset->number_of_columns);
		ft_strdel((char **)&file_params.line);
	}
	ft_strdel((char **)&file_params.line);
	close(file_params.fd);
	return (dataset);
}

const t_dataset	*dataset_initialize(
							const char *const dataset_file_path)
{
	const t_dataset	*dataset;

	dataset = dataset_read_file(dataset_file_path);
	return (dataset);
}

void	dataset_value_array_remove(void *content, size_t size)
{
	const char		***value_array;

	(void)size;
	value_array = (const char ***)content;
	ft_strarraydel(value_array);
	return ;
}
