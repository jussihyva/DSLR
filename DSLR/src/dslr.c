/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:56:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/07 18:58:30 by jkauppi          ###   ########.fr       */
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
					const t_input_params **const input_params)
{
	t_bool			print_leaks;

	print_leaks = (*input_params)->print_leaks;
	input_params_remove(input_params);
	arg_parser_remove(arg_parser);
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
	t_tls_connection		*influxdb_connection;

	arg_parser = arg_parser_init(&argc, &argv);
	input_params = ft_arg_parser(arg_parser);
	influxdb_connection = ft_influxdb_connect("127.0.0.1", "8086");
	ft_influxdb_write(influxdb_connection, "mem,host=host1 used_percent=23.43234543 1631028679", "Hive");
	main_remove(&arg_parser, &input_params);
	ft_printf("Hello from TensorFlow C library version %s\n", TF_Version());
	return (0);
}
