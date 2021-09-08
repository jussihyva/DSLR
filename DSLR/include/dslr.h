/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:54:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/08 20:25:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSLR_H
# define DSLR_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"
# include <stdio.h>
# include "tensorflow/c/c_api.h"

# define	NUMBER_OF_INFLUXDB_TOKENS		2

static const char	*g_influxdb_token_array[NUMBER_OF_INFLUXDB_TOKENS] =
{
	"XPsT1o3pZQUWNsPqXoL4mCCdU-LBPzSpSnVyDYWDV9vi"
	"YS0XHr9itzC-gDNQLb205Fe7IFcsljgP7eNSPyqUsw==",
	"BbEksKgeBUimgSgQ2tkveQWnfIbyQSTp9QqQy-Zlcwus"
	"x8HE70Ux4IGUBIoC6njswxdI0he-GZudPl5YC_2qHA=="
};

typedef struct s_file_params
{
	int		fd;
	char	*line;
}				t_file_params;

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
void			dataset_value_array_remove(void *contnet, size_t size);

#endif
