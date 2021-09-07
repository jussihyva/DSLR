/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:56:21 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/07 10:31:28 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"
#include <stdio.h>
#include "../lib/libtensorflow/include/tensorflow/c/c_api.h"

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

	arg_parser = arg_parser_init(&argc, &argv);
	input_params = ft_arg_parser(arg_parser);
	main_remove(&arg_parser, &input_params);
	ft_printf("Hello from TensorFlow C library version %s\n", TF_Version());
	return (0);
}
