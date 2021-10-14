/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:05:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 18:16:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

t_input_params	*input_params_initialize(
						t_argc_argv *argc_argv)
{
	t_input_params			*input_params;

	input_params = ft_memalloc(sizeof(*input_params));
	input_params->argc_argv = argc_argv;
	input_params->logging_level = LOG_WARN;
	input_params->logging_data = ft_event_logging_init(DEFAULT_LOGGING_LEVEL);
	input_params->hyper_parameters.iterations = ITERATION_LOOP;
	input_params->hyper_parameters.learning_rate = LEARNING_RATE;
	return (input_params);
}

static void	input_param_save_short(
								t_input_params *const input_params,
								char opt,
								t_argc_argv *argc_argv)
{
	t_hyper_parameters	*hyper_parameters;

	hyper_parameters = &input_params->hyper_parameters;
	if (opt == 'L')
		input_params->logging_level = set_logging_level(argc_argv);
	else if (opt == 'S')
		input_params->is_influxdb = E_TRUE;
	else if (opt == 'A')
		hyper_parameters->learning_rate = set_learning_rate(argc_argv);
	else if (opt == 'I')
		hyper_parameters->iterations = set_number_of_iteration_loops(argc_argv);
	else if (opt == 'l')
		input_params->print_leaks = E_TRUE;
	else if (opt == 'h')
		usage_print();
	return ;
}

void	input_param_save(
					void *const input_params,
					char opt, t_argc_argv *argc_argv,
					t_cmd_param_type cmd_param_type)
{
	if (cmd_param_type == E_OPTIONAL_SHORT)
		input_param_save_short(input_params, opt, argc_argv);
	else
		input_param_mandatory_validate(input_params, opt, argc_argv);
	return ;
}

void	input_params_remove(
						const t_input_params **input_params)
{
	const t_dataset	*dataset;

	dataset = (*input_params)->dataset;
	if (dataset)
	{
		ft_strdel((char **)&dataset->file_path);
		ft_strarraydel((const char ***const)&dataset->column_name_array);
		ft_lstdel((t_list **)&dataset->example_lst, example_remove);
		dataaset_stat_remove((t_dataset_stat **)&dataset->stat);
		ft_memdel((void **)&(*input_params)->dataset);
	}
	ft_logging_release(
		(const t_logging_data **const) &(*input_params)->logging_data);
	ft_memdel((void **)input_params);
	return ;
}
