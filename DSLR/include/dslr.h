/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:54:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/15 18:56:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSLR_H
# define DSLR_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"
# include <stdio.h>
# include "tensorflow/c/c_api.h"

# define	NUMBER_OF_INFLUXDB_TOKENS			2
# define	INFLUXDB_CONNECTION_PROTOCOL		E_TLS
# define	NUMBER_OF_INFLUXDB_LINE_ELEMENTS	4
# define	SPECIAL_CHARS_INFLUXDB_MEASUREMENT	", "
# define	SPECIAL_CHARS_INFLUXDB_TAGS			", ="
# define	SPECIAL_CHARS_INFLUXDB_FIELDS		", ="

static const char	*g_influxdb_token_array[NUMBER_OF_INFLUXDB_TOKENS] =
{
	"l1kVqav1U4vTYrZCuv1crOMwHpUiQAKvzRYwy2V9Mag6"
	"xYRi_CjRmk5SZtOFuIzZDbGDbz7eKgB2_GzDkUeL-A==",
	"BbEksKgeBUimgSgQ2tkveQWnfIbyQSTp9QqQy-Zlcwus"
	"x8HE70Ux4IGUBIoC6njswxdI0he-GZudPl5YC_2qHA=="
};

typedef struct s_file_params
{
	int		fd;
	char	*line;
}				t_file_params;

typedef enum e_influxdb_line_element_type
{
	E_MEASUREMENT,
	E_TAGS,
	E_FIELDS,
	E_TIMESTAMP
}				t_influxdb_line_element_type;

typedef struct s_influxdb_line_element
{
	char		*string;
	size_t		string_length;
}				t_influxdb_line_element;

typedef struct s_dataset
{
	const char		*file_path;
	const char		**column_name_array;
	size_t			*column_length_array;
	size_t			number_of_columns;
	t_list			*value_array_lst;
}				t_dataset;

typedef struct s_input_params
{
	const t_argc_argv		*argc_argv;
	const t_logging_data	*logging_data;
	t_logging_level			logging_level;
	t_bool					print_leaks;
	t_bool					is_influxdb;
	const t_dataset			*dataset;
}				t_input_params;

t_input_params	*input_params_initialize(
					t_argc_argv *argc_argv);
void			input_param_save(
					void *const input_params,
					char opt, t_argc_argv *argc_argv,
					t_cmd_param_type cmd_param_type);
void			usage_print(void);
void			input_params_remove(
					const t_input_params **input_params);
const t_dataset	*dataset_initialize(
					const char *const dataset_file_path);
char			**ft_strsplit_ex(
					char const *s,
					const char c,
					size_t *const num_of_words);
void			dataset_value_array_remove(
					void *contnet,
					size_t size);
time_t			ft_gettime(void);
void			dataset_send_to_influxdb(
					const t_tcp_connection *const influxdb_connection,
					const t_dataset *const dataset);
void			influxdb_line_measurement_create(
					t_influxdb_line_element *measurement_element,
					const char *const measurement);
void			influxdb_line_tags_create(
					t_influxdb_line_element *tags_element,
					const char *const hogwarts_subject,
					const char *const hogwarts_house);
void			influxdb_line_fields_create(
					t_influxdb_line_element *fields_element,
					const char *const value);
void			influxdb_line_timestamp_create(
					t_influxdb_line_element *timestamp_element,
					const size_t utc_time_ms);
size_t			length_calculate(
					const char *special_chars,
					const char *const string);
char			*string_create(
					const char *const special_chars,
					const char *const string,
					size_t string_length);
const char		*influxdb_line_group_create(
					const char **const column_name_array,
					const char **const value_array);
int				main_train(void);

#endif
