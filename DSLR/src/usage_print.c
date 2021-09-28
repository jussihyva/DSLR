/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 11:21:35 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/28 13:20:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	examples_print(void)
{
	ft_printf("\n\n Examples:\n");
	ft_printf("\n   1:\n");
	ft_printf("    ./dslr L data/dataset_train.csv\n");
	ft_printf("\n   2:\n");
	ft_printf("    ./dslr T data/dataset_test.csv\n");
	return ;
}

void	usage_print(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./dslr <mode> <input file>\n");
	examples_print();
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  <mode>                    L --> Learning (training phase)\n");
	ft_printf("                            T --> Test\n");
	ft_printf("  <input file>              "
		"A file with data for learning or test phases\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -h                        Help printout\n");
	ft_printf("  -l                        %s\n",
		"Print leaks. Only in MAC-OS");
	exit(42);
}
