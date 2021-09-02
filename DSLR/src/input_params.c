/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:05:30 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/02 15:57:26 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

t_input_params	*input_params_initialize(
						t_argc_argv *argc_argv)
{
	t_input_params			*input_params;

	input_params = ft_memalloc(sizeof(*input_params));
	input_params->argc_argv = argc_argv;
	input_params->event_logging_level = LOG_WARN;
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
		input_params->event_logging_level
			= ft_logging_level_param_validate(arg);
	}
	else if (opt == 'l')
		input_params->print_leaks = E_TRUE;
	else if (opt == 'h')
		usage_print();
	return ;
}

static void	input_param_save_mandatory(
									t_input_params *const input_params,
									char opt,
									t_argc_argv *argc_argv)
{
	const char			*arg;

	(void)opt;
	arg = (*argc_argv->argv)[argc_argv->i];
	if (((*argc_argv->argc) - argc_argv->i) == 1)
		input_params->dataset_file = (const char *)ft_strdup(arg);
	else
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
		input_param_save_mandatory(input_params, opt, argc_argv);
	return ;
}

void	input_params_remove(
						const t_input_params **input_params)
{
	ft_strdel((char **)&(*input_params)->dataset_file);
	ft_memdel((void **)input_params);
	return ;
}
