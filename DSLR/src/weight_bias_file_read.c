/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weight_bias_file_read.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:01:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 10:49:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

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

	param_value = ft_strsplit_ex(line, ':', &num_of_values, E_FALSE);
	if (num_of_values != (NUMBER_OF_HOGWARTS_COURSES + 1))
		FT_LOG_ERROR("Content of the file %s (line=%lu) is not valid!",
			WEIGHT_BIAS_FILE_NAME, line_nbr);
	else
	{
		i = -1;
		while (++i < (NUMBER_OF_HOGWARTS_COURSES + 1))
		{
			errno = 0;
			if (i == 0)
				*bias_value = strtod(param_value[i], &endptr);
			else
				weight_row[i - 1] = strtod(param_value[i], &endptr);
			if (errno != 0 || *endptr != '\0')
				FT_LOG_ERROR("Content of the file %s (line=%lu) is not valid!",
					WEIGHT_BIAS_FILE_NAME, line_nbr);
		}
	}
	ft_strarraydel(&param_value);
}

static void	read_weight_bias_values(
								const char *const weight_bias_file_yaml,
								const int fd,
								t_matrix *const weight,
								t_vector *const bias)
{
	char		*line;
	size_t		i;

	line = NULL;
	i = 0;
	while (ft_get_next_line(fd, &line) > 0)
	{
		if (i >= NUMBER_OF_HOGWARTS_HOUSES)
			FT_LOG_ERROR("%s file includes unexpected number of lines!",
				weight_bias_file_yaml);
		parse_weight_bias_values(line, i + 1, ((double **)weight->values)[i],
			&((double **)bias->values)[i][0]);
		FT_LOG_DEBUG("%s", line);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	return ;
}

void	weight_bias_read(
				t_matrix *weight,
				t_vector *bias)
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
