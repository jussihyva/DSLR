/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dslr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 21:54:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/02 11:42:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSLR_H
# define DSLR_H
# include "libft.h"
# include "ft_printf.h"
# include "libft_addons.h"

typedef struct s_input_params
{
	t_argc_argv			*argc_argv;
	t_loging_level		event_logging_level;
	t_bool				print_leaks;
}				t_input_params;

void	*input_params_init(
			t_argc_argv *argc_argv);
void	input_param_save(
			void *input_params,
			char opt, t_argc_argv *argc_argv,
			t_cmd_param_type cmd_param_type);
void	usage_print(
			void);

#endif
