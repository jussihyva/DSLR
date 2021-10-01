/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_params_mandatory.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 09:43:42 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/01 09:47:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	check_number_of_mandatory_variables(t_argc_argv *argc_argv)
{
	static t_bool	is_num_of_mandatory_variables_valid = E_FALSE;
	size_t			num_of_mandatory_variables;

	if (!is_num_of_mandatory_variables_valid)
	{
		num_of_mandatory_variables = *argc_argv->argc - argc_argv->i;
		if (num_of_mandatory_variables == 2)
			is_num_of_mandatory_variables_valid = E_TRUE;
		else
			usage_print();
	}
	return ;
}

void	input_param_mandatory_validate(
								t_input_params *const input_params,
								char opt,
								t_argc_argv *argc_argv)
{
	const char		*arg;
	const char		*dataset_file_path;

	(void)opt;
	check_number_of_mandatory_variables(argc_argv);
	arg = (*argc_argv->argv)[argc_argv->i];
	if (((*argc_argv->argc) - argc_argv->i) == 1)
	{
		dataset_file_path = (const char *)ft_strdup(arg);
		input_params->dataset = dataset_initialize(dataset_file_path);
	}
	else if (((*argc_argv->argc) - argc_argv->i) == 2)
	{
		if (ft_strequ(arg, LEARNING_MODE))
			input_params->mode = E_LEARNING_MODE;
		else if (ft_strequ(arg, TEST_MODE))
			input_params->mode = E_TEST_MODE;
		else
			usage_print();
	}
	else
		usage_print();
	return ;
}
