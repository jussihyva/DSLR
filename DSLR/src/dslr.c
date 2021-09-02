/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:56:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/02 15:55:14 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static t_arg_parser	*arg_parser_init(const int *argc, const char ***argv)
{
	t_arg_parser	*arg_parser;

	arg_parser = ft_memalloc(sizeof(*arg_parser));
	arg_parser->argc_argv.argc = argc;
	arg_parser->argc_argv.argv = argv;
	arg_parser->fn_input_params_initialize = (void *)input_params_initialize;
	arg_parser->fn_input_param_save = input_param_save;
	arg_parser->fn_usage_print = usage_print;
	arg_parser->options = ft_strdup("L:hl");
	return (arg_parser);
}

static void	arg_parser_remove(t_arg_parser **arg_parser)
{
	ft_strdel((char **)&(*arg_parser)->options);
	ft_memdel((void **)arg_parser);
	return ;
}

static void	main_remove(
					t_arg_parser **arg_parser,
					t_event_logging_data **event_logging_data,
					const t_input_params **input_params)
{
	t_bool			print_leaks;

	print_leaks = (*input_params)->print_leaks;
	input_params_remove(input_params);
	arg_parser_remove(arg_parser);
	ft_event_logging_release(event_logging_data);
	if (print_leaks)
		ft_print_leaks("dslr");
	return ;
}

int	main(
	const int argc,
	const char **argv)
{
	t_arg_parser			*arg_parser;
	const t_input_params	*input_params;
	t_event_logging_data	*event_logging_data;

	arg_parser = arg_parser_init(&argc, &argv);
	input_params = ft_arg_parser(arg_parser);
	event_logging_data = ft_event_logging_init(
			input_params->event_logging_level);
	main_remove(&arg_parser, &event_logging_data, &input_params);
	return (0);
}
