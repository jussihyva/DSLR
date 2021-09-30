/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:54:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 09:20:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSLR_H
# define DSLR_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>

# define NUMBER_OF_INFLUXDB_TOKENS			2
# define INFLUXDB_CONNECTION_PROTOCOL		E_TLS
# define NUMBER_OF_INFLUXDB_LINE_ELEMENTS	4
# define SPECIAL_CHARS_INFLUXDB_MEASUREMENT	", "
# define SPECIAL_CHARS_INFLUXDB_TAGS			", ="
# define SPECIAL_CHARS_INFLUXDB_FIELDS		", ="
# define NUMBER_OF_HOGWARTS_COURSES			13
# define NUMBER_OF_HOGWARTS_HOUSES			4
# define LEARNING_RATE						0.2
# define ITERATION_LOOP						10000
# define WEIGHT_BIAS_FILE_NAME				"weight_bias_values.yaml"
# define WRITE_BUF_SIZE						1000
# define SUB_STRING_MAX_LENGTH				100
# define LEARNING_MODE						"L"
# define TEST_MODE							"T"

static const char	*g_influxdb_token_array[NUMBER_OF_INFLUXDB_TOKENS] =
{
	"l1kVqav1U4vTYrZCuv1crOMwHpUiQAKvzRYwy2V9Mag6"
	"xYRi_CjRmk5SZtOFuIzZDbGDbz7eKgB2_GzDkUeL-A==",
	"BbEksKgeBUimgSgQ2tkveQWnfIbyQSTp9QqQy-Zlcwus"
	"x8HE70Ux4IGUBIoC6njswxdI0he-GZudPl5YC_2qHA=="
};

static const char	*g_hogwarts_house_array[NUMBER_OF_HOGWARTS_HOUSES] =
{
	"Gryffindor",
	"Ravenclaw",
	"Slytherin",
	"Hufflepuff"
};

typedef enum e_mode
{
	E_NO_MODE,
	E_LEARNING_MODE,
	E_TEST_MODE
}				t_mode;

typedef enum e_vector_type
{
	E_DIR_ROW,
	E_DIR_COLUMN
}				t_vector_type;

typedef enum e_content_type
{
	E_INT,
	E_DOUBLE
}				t_content_type;

typedef enum e_sign
{
	E_MINUS,
	E_PLUS
}				t_sign;

typedef struct s_file_params
{
	int		fd;
	char	*line;
}				t_file_params;

typedef enum e_regression_type
{
	E_LINEAR,
	E_LOGISTIC
}				t_regression_type;

typedef enum e_influxdb_line_element_type
{
	E_MEASUREMENT,
	E_TAGS,
	E_FIELDS,
	E_TIMESTAMP
}				t_influxdb_line_element_type;

typedef struct s_matrix
{
	t_matrix_size	size;
	void			**values;
}				t_matrix;

typedef t_matrix	t_vector;

typedef struct s_min_max_value
{
	const t_vector	*min_value;
	const t_vector	*max_value;
	t_vector		*range;
}				t_min_max_value;

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
	size_t			number_of_rows;
	t_list			*value_array_lst;
}				t_dataset;

typedef struct s_input_params
{
	const t_argc_argv		*argc_argv;
	const t_logging_data	*logging_data;
	t_logging_level			logging_level;
	t_bool					print_leaks;
	t_bool					is_influxdb;
	t_mode					mode;
	const t_dataset			*dataset;
}				t_input_params;

typedef struct s_gradient_descent
{
	const t_matrix	*observed;
	const t_matrix	*input_values;
	t_matrix		*weight;
	t_vector		*bias;
}				t_gradient_descent;

typedef struct s_derivative
{
	t_matrix	*weight;
	t_vector	*bias;
}				t_derivative;

t_input_params			*input_params_initialize(
							t_argc_argv *argc_argv);
void					input_param_save(
							void *const input_params,
							char opt, t_argc_argv *argc_argv,
							t_cmd_param_type cmd_param_type);
void					usage_print(void);
void					input_params_remove(
							const t_input_params **input_params);
const t_dataset			*dataset_initialize(
							const char *const dataset_file_path);
const char				**ft_strsplit_ex(
							char const *s,
							const char c,
							size_t *const num_of_words);
void					dataset_value_array_remove(
							void *contnet,
							size_t size);
time_t					ft_gettime(void);
void					dataset_send_to_influxdb(
							const t_tcp_connection *const connection,
							const t_dataset *const dataset);
void					influxdb_line_measurement_create(
							t_influxdb_line_element *measurement_element,
							const char *const measurement);
void					influxdb_line_tags_create(
							t_influxdb_line_element *tags_element,
							const char *const hogwarts_subject,
							const char *const hogwarts_house);
void					influxdb_line_tags_create_2(
							t_influxdb_line_element *tags_element,
							const char *const index,
							const char *const hogwarts_house);
void					influxdb_line_fields_create(
							t_influxdb_line_element *fields_element,
							const char *const index,
							const char *const value);
void					influxdb_line_fields_create_2(
							t_influxdb_line_element *fields_element,
							const char **const column_name_array,
							const char **const value_array);
void					influxdb_line_timestamp_create(
							t_influxdb_line_element *timestamp_element,
							const size_t utc_time_ms);
char					*backslash_chars_add(
							const char *const special_chars,
							const char *const string);
const char				*influxdb_line_group_create(
							const char **const column_name_array,
							const char **const value_array);
int						main_train(void);
t_gradient_descent		*gradient_descent_initialize(
							t_regression_type regression_type,
							const t_dataset *const dataset);
t_matrix				*ft_matrix_create(
							size_t size,
							const size_t number_fo_rows,
							const size_t number_of_columns);
t_vector				*ft_vector_create(
							size_t size,
							size_t length,
							t_vector_type vector_type);
void					gradient_descent_iteration(
							const t_regression_type regression_type,
							const t_gradient_descent *const gradient_descent);
void					ft_matrix_dot_matrix(
							const t_matrix *const matrix1,
							const t_matrix *const matrix2,
							t_matrix *const new_matrix);
t_matrix				*ft_matrix_transpose(const t_matrix *const matrix);
t_vector				*ft_vector_transpose(const t_vector *const vector);
void					ft_matrix_add_vector(
							const t_matrix *const matrix,
							const t_vector *const vector,
							t_matrix *const new_matrix);
void					ft_matrix_exp_double(
							const t_matrix *const matrix,
							t_matrix *const new_matrix,
							const t_sign sign);
void					ft_vector_div_double(
							const t_vector *const vector,
							const double value,
							t_vector *const new_vector);
void					ft_double_div_vector(
							const double value,
							const t_vector *const vector,
							t_vector *const new_vector);
void					ft_matrix_print(
							const char *const matrix_name,
							const t_matrix *const matrix,
							const t_content_type content_type);
void					ft_vector_print(
							const char *const vectior_name,
							const t_vector *const vector,
							const t_content_type content_type);
const t_matrix			*residual_calculate(
							const t_matrix *const observed,
							const t_matrix *const predicted);
void					ft_matrix_subtract_matrix(
							const t_matrix *const matrix1,
							const t_matrix *const matrix2,
							t_matrix *const new_matrix);
const t_vector			*ft_matrix_sum(
							const t_matrix *const matrix,
							const t_vector_type vector_type);
void					ft_vector_abs_double(
							const t_vector *const vector,
							t_vector *const new_vector);
void					ft_matrix_dot_vector_double(
							const t_matrix *const matrix,
							const t_vector *const vector,
							t_vector *const new_vector);
void					ft_vector_add_vector(
							const t_vector *const vector1,
							const t_vector *const vector2,
							t_vector *const new_vector);
void					ft_matrix_add_double(
							const t_matrix *const matrix,
							const double value,
							t_vector *const new_matrix);
void					ft_vector_add_double(
							const t_vector *const vector,
							const double value,
							t_vector *const new_vector);
void					ft_shape_print(
							const char *const matrix_name,
							const t_matrix *const matrix);
const t_vector			*cost_calculate(
							const t_matrix *const predicted,
							const t_matrix *const observed);
void					ft_matrix_log(
							const t_matrix *const matrix,
							t_matrix *const new_matrix,
							const t_sign sign);
void					ft_double_subtract_matrix(
							const double value,
							const t_matrix *const matrix,
							t_matrix *const new_matrix);
void					ft_matrix_multiply_matrix(
							const t_matrix *const matrix1,
							const t_matrix *const matrix2,
							t_matrix *const new_matrix);
void					ft_matrix_add_matrix(
							const t_matrix *const matrix1,
							const t_matrix *const matrix2,
							t_matrix *const new_matrix);
const t_matrix			*ft_matrix_normalize(
							const t_matrix *const matrix,
							const t_vector_type vector_type);
const t_vector			*ft_matrix_min(
							const t_matrix *const matrix,
							const t_vector_type vector_type);
const t_vector			*ft_matrix_max(
							const t_matrix *const matrix,
							const t_vector_type vector_type);
void					ft_matrix_div_vector(
							const t_matrix *const matrix,
							const t_vector *const vector,
							t_matrix *const new_matrix);
void					ft_matrix_subtract_vector(
							const t_matrix *const matrix,
							const t_vector *const vector,
							t_matrix *const new_matrix);
void					weight_bias_save(
							const t_matrix *const weight,
							const t_vector *const bias);
void					weight_bias_read(
							t_matrix **weight,
							t_vector **bias);
void					ft_matrix_remove(t_matrix **matrix);
void					ft_vector_remove(t_vector **vector);
void					gradient_descent_remove(
							t_gradient_descent **gradient_descent);
char					*ft_file_path_create(char *file_name);

#endif
