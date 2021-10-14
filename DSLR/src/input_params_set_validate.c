/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_params_set_validate.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:04:33 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 18:17:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

t_logging_level	set_logging_level(const t_argc_argv *const argc_argv)
{
	const char			*arg;
	t_logging_level		logging_level;

	arg = (*argc_argv->argv)[argc_argv->i];
	logging_level = ft_logging_level_param_validate(arg);
	ft_log_set_level(logging_level);
	return (logging_level);
}

double	set_learning_rate(const t_argc_argv *const argc_argv)
{
	const char		*arg;
	char			*endptr;
	double			learning_rate;

	errno = 0;
	arg = (*argc_argv->argv)[argc_argv->i];
	learning_rate = strtod(arg, &endptr);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -A is not valid");
	if (learning_rate > 1)
		FT_LOG_ERROR("Maximum value for learning rate (-A) is 1");
	if (learning_rate <= 0)
		FT_LOG_ERROR("Minimum value for learning rate (-A) is >0");
	return (learning_rate);
}

double	set_number_of_iteration_loops(const t_argc_argv *const argc_argv)
{
	const char		*arg;
	char			*endptr;
	size_t			iterations;

	errno = 0;
	arg = (*argc_argv->argv)[argc_argv->i];
	iterations = ft_strtoi(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -I is not valid");
	if (iterations > 100000)
		FT_LOG_ERROR("Maximum value for learning rate (-I) is "
			"100000 (100 thousand)");
	if (iterations <= 0)
		FT_LOG_ERROR("Minimum value for learning rate (-I) is >0");
	return (iterations);
}
