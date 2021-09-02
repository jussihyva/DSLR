/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dataset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:06:27 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/02 17:56:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

void	dataset_read_file(const char *const file_path)
{
	t_file_params		file_params;
	// t_index_name_pair	*index_name_pair;

	file_params.fd = ft_open_fd(file_path);
	file_params.line = NULL;
	ft_get_next_line(file_params.fd, &file_params.line);
	ft_strdel((char **)&file_params.line);
	while (ft_get_next_line(file_params.fd, &file_params.line) > 0)
	{
		ft_printf("%s\n", file_params.line);
		ft_strdel((char **)&file_params.line);
	}
	ft_strdel((char **)&file_params.line);
	close(file_params.fd);
	return ;
}

t_dataset	*dataset_initialize(const char *const dataset_file_path)
{
	t_dataset		*dataset;

	dataset = ft_memalloc(sizeof(*dataset));
	dataset->file_path = dataset_file_path;
	dataset_read_file(dataset->file_path);
	return (dataset);
}
