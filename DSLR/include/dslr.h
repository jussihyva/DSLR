/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:54:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 18:13:32 by jkauppi          ###   ########.fr       */
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
# include <float.h>

# define NUMBER_OF_INFLUXDB_TOKENS			2
# define INFLUXDB_CONNECTION_PROTOCOL		E_TLS
# define NUMBER_OF_INFLUXDB_LINE_ELEMENTS	4
# define SPECIAL_CHARS_INFLUXDB_MEASUREMENT	", "
# define SPECIAL_CHARS_INFLUXDB_TAGS		", ="
# define SPECIAL_CHARS_INFLUXDB_FIELDS		", ="
# define NUMBER_OF_HOGWARTS_COURSES			13
# define NUMBER_OF_HOGWARTS_HOUSES			4
# define LEARNING_RATE						0.2
# define ITERATION_LOOP						5000
# define WEIGHT_BIAS_FILE_NAME				"weight_bias_values.yaml"
# define HOUSES_RESULT_FILE_NAME			"houses.csv"
# define WRITE_BUF_SIZE						1000
# define SUB_STRING_MAX_LENGTH				100
# define TRAIN_MODE							"TRAIN"
# define TEST_MODE							"TEST"
# define NUMBER_OF_INPUT_FUNCTIONS			13

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

static const size_t	g_function_columns[NUMBER_OF_INPUT_FUNCTIONS] =
{
	6, 7, 8, 9, 10,
	11, 12, 13, 14, 15,
	16, 17, 18
};

typedef enum e_influxdb_line_type
{
	E_INDEX_BASED,
	E_SUBJECT_BASED
}				t_influxdb_line_type;

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

typedef struct s_example
{
	const char		**value_array;
	double			*double_value_array;
	t_bool			are_all_values_valid;
	t_bool			*validity_array;
}				t_example;

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

typedef struct s_dataset_stat
{
	double		*sum_array;
	size_t		*num_of_values_array;
	double		*mean_array;
}				t_dataset_stat;

typedef struct s_dataset
{
	const char				*file_path;
	const char				**column_name_array;
	size_t					number_of_columns;
	size_t					number_of_rows;
	t_list					*example_lst;
	const t_dataset_stat	*stat;
}				t_dataset;

typedef struct s_hyper_parameters
{
	size_t					iterations;
	double					learning_rate;
}				t_hyper_parameters;

typedef struct s_input_params
{
	const t_argc_argv		*argc_argv;
	const t_logging_data	*logging_data;
	t_logging_level			logging_level;
	t_bool					print_leaks;
	t_bool					is_influxdb;
	t_mode					mode;
	const t_dataset			*dataset;
	t_hyper_parameters		hyper_parameters;
}				t_input_params;

typedef struct s_gradient_descent
{
	const t_matrix				*observed;
	const t_matrix				*input_values;
	t_matrix					*weight;
	t_vector					*bias;
	t_vector					*cost;
	const t_hyper_parameters	*hyper_parameters;
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
							size_t *const num_of_words,
							t_bool do_trim);
void					example_remove(
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
							t_influxdb_line_element *timestamp_element);
char					*backslash_chars_add(
							const char *const special_chars,
							const char *const string);
const char				*influxdb_line_group_create(
							const char **const column_name_array,
							const char **const value_array);
int						main_train(void);
t_gradient_descent		*gradient_descent_initialize(
							t_regression_type regression_type,
							const t_dataset *const dataset,
							const t_hyper_parameters *const hyper_parameters);
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
							const t_gradient_descent *const gradient_descent,
							const t_tcp_connection *const connection);
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
void					ft_matrix_div_double(
							const t_matrix *const matrix,
							const double value,
							t_matrix *const new_matrix);
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
const t_vector			*cost_recalculate(
							const t_matrix *const predicted,
							const t_matrix *const observed,
							t_vector *const cost);
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
void					weight_bias_write(
							const t_matrix *const weight,
							const t_vector *const bias);
void					weight_bias_read(
							t_matrix *weight,
							t_vector *bias);
void					ft_matrix_remove(t_matrix **matrix);
void					ft_vector_remove(t_vector **vector);
void					gradient_descent_remove(
							t_gradient_descent **gradient_descent);
char					*ft_file_path_create(char *file_name);
t_derivative			*derivative_initialize(
							const t_matrix *const input_values,
							const t_matrix *const observed);
void					derivative_remove(t_derivative **derivative);
void					leayer_calculate(
							const t_regression_type regression_type,
							const t_gradient_descent *const gradient_descent,
							const t_derivative *const derivative,
							const double learning_rate);
const t_matrix			*ft_sigmoid(const t_matrix *const input);
void					derivative_recalculate(
							const t_matrix *const activation_input,
							const t_matrix *const observed,
							const t_matrix *const predicted,
							const t_derivative *const derivative);
void					input_param_mandatory_validate(
							t_input_params *const input_params,
							char opt,
							t_argc_argv *argc_argv);
size_t					influxdb_line_subject_based_create(
							const char **const value_array,
							const char **const column_name_array,
							const size_t i,
							t_queue *queue);
size_t					influxdb_line_length_calculate(
							t_influxdb_line_element *influxdb_line_element);
const char				*elements_merge(
							t_influxdb_line_element *const
							influxdb_line_element);
char					*ft_strcat_queue(
							t_queue *const queue,
							const size_t string_length);
const t_matrix			*predict(
							t_regression_type regression_type,
							const t_matrix *const activation_input,
							const t_vector *bias,
							const t_matrix *const weight);
void					gradient_descent_predict(
							t_gradient_descent *const gradient_descent);
const t_vector			*ft_matrix_argmax(
							const t_matrix *const matrix,
							const t_vector_type vector_type);
void					ft_vector_set(
							t_vector *const vector,
							const double value);
char					*ft_str_toupper(const char *const str);
void					example_validate_and_statistics_update(
							t_example *const example,
							const size_t number_of_values,
							const t_dataset_stat *stat);
const t_dataset_stat	*dataset_stat_initialize(
							const size_t number_of_columns);
void					dataaset_stat_remove(t_dataset_stat **stat);
void					prediction_validate(
							const t_matrix *const observed,
							const t_vector *const predicted_argmax);
void					ft_queue_remove(t_queue **queue);
size_t					name_value_pair_add(
							const char *const name,
							const char *const value,
							t_queue *const queue_str,
							const char *const special_chars);
size_t					delimiter_add(
							t_queue *queue,
							const char *const delimiter);
t_logging_level			set_logging_level(const t_argc_argv *const argc_argv);
double					set_learning_rate(const t_argc_argv *const argc_argv);
double					set_number_of_iteration_loops(
							const t_argc_argv *const argc_argv);

#endif
