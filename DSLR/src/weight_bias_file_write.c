/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight_bias_file_write.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:59:36 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 13:31:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static size_t	weight_values_add(
						t_queue *const queue,
						const double *const weight_row,
						const size_t columns)
{
	size_t		string_length;
	char		*substring;
	size_t		i;

	string_length = 0;
	i = -1;
	while (++i < columns)
	{
		ft_enqueue(queue, (void *)ft_strdup(":"));
		string_length++;
		substring = ft_strnew(SUB_STRING_MAX_LENGTH);
		ft_sprintf(substring, "%f", weight_row[i]);
		ft_enqueue(queue, (void *)substring);
		string_length += ft_strlen(substring);
	}
	return (string_length);
}

static const char	*strings_merge(
							t_queue *const queue,
							const size_t string_length)
{
	char		*str;
	const char	*substring;

	str = ft_strnew(string_length);
	while (!ft_is_queue_empty(queue))
	{
		substring = (char *)ft_dequeue(queue);
		ft_strcat(str, substring);
		ft_strdel((char **)&substring);
	}
	return (str);
}

static const char	*yaml_string_create(
							const double *const weight_row,
							const double *const bias_row,
							const size_t columns)
{
	t_queue		*queue;
	char		*substring;
	size_t		string_length;
	const char	*str;

	queue = ft_queue_init();
	string_length = 0;
	substring = ft_strnew(SUB_STRING_MAX_LENGTH);
	ft_sprintf(substring, "%f", bias_row[0]);
	ft_enqueue(queue, (void *)substring);
	string_length += ft_strlen(substring);
	string_length += weight_values_add(queue, weight_row, columns);
	ft_enqueue(queue, (void *)ft_strdup("\n"));
	string_length++;
	str = strings_merge(queue, string_length);
	ft_queue_remove(&queue);
	return (str);
}

void	weight_bias_write(
				const t_matrix *const weight,
				const t_vector *const bias)
{
	const char		*write_buf;
	char			*weight_bias_file_yaml;
	int				fd;
	ssize_t			ret;
	size_t			i;

	ft_matrix_print("WEIGHT", weight, E_DOUBLE);
	ft_matrix_print("BIAS", bias, E_DOUBLE);
	weight_bias_file_yaml = ft_file_path_create(WEIGHT_BIAS_FILE_NAME);
	remove(weight_bias_file_yaml);
	fd = open(weight_bias_file_yaml, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	i = -1;
	while (++i < weight->size.rows)
	{
		write_buf = yaml_string_create(weight->values[i], bias->values[i],
				weight->size.columns);
		ret = write(fd, write_buf, ft_strlen(write_buf));
		ft_strdel((char **)&write_buf);
	}
	ret = close(fd);
	ft_strdel(&weight_bias_file_yaml);
	return ;
}
