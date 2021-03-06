/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:56:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/24 16:34:24 by juhani           ###   ########.fr       */
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
	arg_parser->options = ft_strdup("L:hlA:I:S");
	return (arg_parser);
}

static void	arg_parser_remove(t_arg_parser **arg_parser)
{
	ft_strdel((char **)&(*arg_parser)->options);
	ft_memdel((void **)arg_parser);
	return ;
}

static void	influxdb_remove(const t_tcp_connection **influxdb_connection)
{
	if (*influxdb_connection)
	{
		SSL_shutdown((*influxdb_connection)->ssl_bio);
		SSL_free((*influxdb_connection)->ssl_bio);
		SSL_CTX_free((*influxdb_connection)->ctx);
		ft_memdel((void **)influxdb_connection);
	}
	return ;
}

static void	main_remove(
					t_arg_parser **arg_parser,
					const t_input_params **const input_params,
					const t_tcp_connection **const influxdb_connection,
					t_gradient_descent **gradient_descent)
{
	t_bool			print_leaks;

	print_leaks = (*input_params)->print_leaks;
	if (*influxdb_connection)
		influxdb_remove(influxdb_connection);
	input_params_remove(input_params);
	arg_parser_remove(arg_parser);
	gradient_descent_remove(gradient_descent);
	if (print_leaks)
		ft_print_leaks("dslr");
	return ;
}

int	main(
	const int argc,
	const char **argv)
{
	t_arg_parser				*arg_parser;
	const t_input_params		*input_params;
	const t_tcp_connection		*connection;
	t_gradient_descent			*gradient_descent;

	arg_parser = arg_parser_init(&argc, &argv);
	input_params = ft_arg_parser(arg_parser);
	if (input_params->mode == E_NO_MODE)
		usage_print();
	connection = ft_influxdb_connect("127.0.0.1", "8086",
			INFLUXDB_CONNECTION_PROTOCOL);
	if (input_params->is_influxdb && connection && input_params->dataset)
		dataset_send_to_influxdb(connection, input_params->dataset);
	gradient_descent = gradient_descent_initialize(E_LOGISTIC,
			input_params->dataset, &input_params->hyper_parameters);
	if (input_params->mode == E_LEARNING_MODE)
	{
		gradient_descent_iteration(input_params->dataset, gradient_descent,
			connection, input_params->is_influxdb);
		ft_matrix_print("COST", gradient_descent->cost, E_DOUBLE);
	}
	else if (input_params->mode == E_TEST_MODE)
		gradient_descent_predict(gradient_descent);
	main_remove(&arg_parser, &input_params, &connection, &gradient_descent);
	return (0);
}
