/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight_bias_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:01:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 12:16:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const char	*yaml_string_create(
							const double *const weight_row,
							const double *const bias_row,
							const size_t columns)
{
	t_queue		*queue;
	size_t		i;
	char		*substring;
	size_t		string_length;
	char		*str;

	queue = ft_queue_init();
	string_length = 0;
	substring = ft_strnew(SUB_STRING_MAX_LENGTH);
	ft_sprintf(substring, "%f", bias_row[0]);
	ft_enqueue(queue, (void *)substring);
	string_length += ft_strlen(substring);
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
	ft_enqueue(queue, (void *)ft_strdup("\n"));
	string_length++;
	str = ft_strnew(string_length);
	while (!ft_is_queue_empty(queue))
	{
		substring = (char *)ft_dequeue(queue);
		ft_strcat(str, substring);
		ft_strdel(&substring);
	}
	ft_memdel((void **)&queue->in_stack);
	ft_memdel((void **)&queue->out_stack);
	ft_memdel((void **)&queue);
	return (str);
}

void	weight_bias_save(
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

static void	parse_weight_bias_values(
							const char *const line,
							const size_t line_nbr,
							double *const weight_row,
							double *bias_value)
{
	const char		**param_value;
	char			*endptr;
	size_t			num_of_values;
	size_t			i;

	param_value = ft_strsplit_ex(line, ':', &num_of_values);
	if (num_of_values != (NUMBER_OF_HOGWARTS_COURSES + 1))
	{
		FT_LOG_ERROR("Content of the file %s (line=%lu) is not valid!",
			WEIGHT_BIAS_FILE_NAME, line_nbr);
	}
	else
	{
		i = -1;
		while (++i < (NUMBER_OF_HOGWARTS_COURSES + 1))
		{
			if (i == 0)
			{
				errno = 0;
				*bias_value = strtod(param_value[i], &endptr);
			}
			else
			{
				errno = 0;
				weight_row[i - 1] = strtod(param_value[i], &endptr);
			}
			if (errno != 0 || *endptr != '\0')
				FT_LOG_ERROR("Content of the file %s (line=%lu) is not valid!",
					WEIGHT_BIAS_FILE_NAME, line_nbr);
		}
	}
	ft_strarraydel(&param_value);
	return ;
}

static void	read_weight_bias_values(
								const char *const weight_bias_file_yaml,
								const int fd,
								t_matrix **const weight,
								t_vector **const bias)
{
	char		*line;
	size_t		i;

	*weight = ft_matrix_create(sizeof(double),
			NUMBER_OF_HOGWARTS_HOUSES, NUMBER_OF_HOGWARTS_COURSES);
	*bias = ft_vector_create(sizeof(double), NUMBER_OF_HOGWARTS_HOUSES,
			E_DIR_ROW);
	line = NULL;
	i = 0;
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (i >= NUMBER_OF_HOGWARTS_HOUSES)
			FT_LOG_ERROR("%s file includes unexpected number of lines!",
				weight_bias_file_yaml);
		parse_weight_bias_values(line, i + 1, ((double **)(*weight)->values)[i],
			&((double **)(*bias)->values)[i][0]);
		FT_LOG_DEBUG("%s", line);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	return ;
}

void	weight_bias_read(
				t_matrix **weight,
				t_vector **bias)
{
	int			fd;
	char		*weight_bias_file_yaml;

	weight_bias_file_yaml = ft_file_path_create(WEIGHT_BIAS_FILE_NAME);
	fd = open(weight_bias_file_yaml, O_RDONLY);
	if (fd > 0)
		read_weight_bias_values(weight_bias_file_yaml, fd, weight, bias);
	else
		FT_LOG_ERROR("WeightBias file (%s) is not created!",
			weight_bias_file_yaml);
	ft_strdel(&weight_bias_file_yaml);
	return ;
}
