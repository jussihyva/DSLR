/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:06:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/19 10:52:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const char	**create_column_arrays(
						const char *const line,
						size_t *number_of_columns)
{
	const char		**column_name_array;
	size_t			i;

	column_name_array = (const char **)ft_strsplit_ex(line, ',',
			number_of_columns, E_FALSE);
	FT_LOG_INFO("%s", line);
	FT_LOG_INFO("Columns:");
	i = -1;
	while (++i < *number_of_columns)
		FT_LOG_INFO("  %s", column_name_array[i]);
	FT_LOG_INFO("Number of columns: %d", *number_of_columns);
	return (column_name_array);
}

static t_example	*example_initialize_validate(
										const char *const line,
										size_t *const number_of_values,
										const t_dataset_stat *stat)
{
	t_example		*example;

	example = ft_memalloc(sizeof(*example));
	example->value_array = (const char **)ft_strsplit_ex(line, ',',
			number_of_values, E_TRUE);
	example->validity_array = ft_memalloc(sizeof(*example->validity_array)
			* *number_of_values);
	example->double_value_array
		= ft_memalloc(sizeof(*example->double_value_array) * *number_of_values);
	example_validate_and_statistics_update(example, *number_of_values, stat);
	if (!(example->are_all_values_valid))
		FT_LOG_DEBUG("All values are not valid: %s", line);
	return (example);
}

static void	dataset_save_record(
							const char *const line,
							t_list **const example_lst,
							const size_t number_of_columns,
							const t_dataset_stat *stat)
{
	size_t			number_of_values;
	const t_list	*new_elem;
	t_example		*example;

	example = example_initialize_validate(line, &number_of_values, stat);
	if (number_of_values != number_of_columns
		|| number_of_columns < NUMBER_OF_INPUT_FUNCTIONS)
	{
		if (ft_log_get_level() <= LOG_TRACE)
			ft_strarray_print(example->value_array);
		ft_printf("%s\n", line);
		FT_LOG_FATAL("FATAL: A content of the dataset file is not valid!");
	}
	new_elem = ft_lstnew(&example, sizeof(example));
	ft_lstadd(example_lst, (t_list *)new_elem);
	if (ft_log_get_level() <= LOG_TRACE)
		ft_strarray_print(example->value_array);
	return ;
}

static const t_dataset	*dataset_read_file(
								const char *const file_path)
{
	t_dataset		*dataset;
	t_file_params	file_params;

	dataset = ft_memalloc(sizeof(*dataset));
	dataset->file_path = file_path;
	file_params.fd = ft_open_fd(file_path);
	file_params.line = NULL;
	dataset->number_of_rows = -1;
	while (ft_get_next_line(file_params.fd, &file_params.line) > 0)
	{
		dataset->number_of_rows++;
		if (dataset->number_of_rows == 0)
		{
			dataset->column_name_array = create_column_arrays(file_params.line,
					&dataset->number_of_columns);
			dataset->stat = dataset_stat_initialize(dataset->number_of_columns);
		}
		else
			dataset_save_record(file_params.line, &dataset->example_lst,
				dataset->number_of_columns, dataset->stat);
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
	if (!dataset->column_name_array || !dataset->number_of_rows)
		FT_LOG_ERROR("Input file is not valid!");
	return (dataset);
}
