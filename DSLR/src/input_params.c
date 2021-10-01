/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:05:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/01 09:46:47 by jkauppi          ###   ########.fr       */
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
	return (input_params);
}

static void	input_param_save_short(
								t_input_params *const input_params,
								char opt,
								t_argc_argv *argc_argv)
{
	const char			*arg;

	if (opt == 'L')
	{
		arg = (*argc_argv->argv)[argc_argv->i];
		input_params->logging_level
			= ft_logging_level_param_validate(arg);
		ft_log_set_level(input_params->logging_level);
	}
	else if (opt == 'I')
		input_params->is_influxdb = E_TRUE;
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
	if ((*input_params)->dataset)
	{
		ft_strdel((char **)&(*input_params)->dataset->file_path);
		ft_memdel((void **)&(*input_params)->dataset->column_length_array);
		ft_strarraydel((const char ***const)&(*input_params)->dataset
			->column_name_array);
		ft_lstdel((t_list **)&(*input_params)->dataset->value_array_lst,
			dataset_value_array_remove);
		ft_memdel((void **)&(*input_params)->dataset);
	}
	ft_logging_release(
		(const t_logging_data **const) &(*input_params)->logging_data);
	ft_memdel((void **)input_params);
	return ;
}
