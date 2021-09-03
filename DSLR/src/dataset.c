/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:06:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/03 12:33:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	create_column_arrays(
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
	ft_printf("%s\n", line);
	ft_printf("Columns:\n");
	i = -1;
	while (++i < dataset->number_of_columns)
	{
		column_name = dataset->column_name_array[i];
		ft_printf("  %s\n", column_name);
		dataset->column_length_array[i] = ft_strlen(column_name);
	}
	return ;
}

const t_dataset	*dataset_read_file(
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
		{
			create_column_arrays(file_params.line, dataset);
			ft_printf("Number of columns: %d\n", dataset->number_of_columns);
		}
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
