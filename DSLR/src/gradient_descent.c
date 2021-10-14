/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:08:19 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/14 10:34:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static size_t	house_index(
					const char *const hogwarts_house,
					const size_t column,
					const t_matrix *const observed)
{
	size_t	house_i;
	int		index;

	index = -1;
	house_i = -1;
	while (++house_i < NUMBER_OF_HOGWARTS_HOUSES)
	{
		if (ft_strequ(hogwarts_house, g_hogwarts_house_array[house_i]))
		{
			index = house_i;
			break ;
		}
	}
	if (index != -1)
	{
		((double **)observed->values)[index][column] = E_TRUE;
		FT_LOG_TRACE("House: %s", hogwarts_house);
	}
	else
		FT_LOG_WARN("Unknown house: %s", hogwarts_house);
	return (index);
}

static void	course_values_add(
						const t_matrix *const input_values,
						const size_t column,
						const double *const value_array)
{
	size_t		i;

	i = -1;
	while (++i < NUMBER_OF_INPUT_FUNCTIONS)
	{
		((double **)input_values->values)[i][column]
			= value_array[g_function_columns[i]];
	}
	return ;
}

static void	input_data_add(
					const t_dataset *const dataset,
					t_gradient_descent *const gradient_descent)
{
	t_matrix			*input_values;
	const t_list		*elem;
	const t_example		*example;
	size_t				i;

	input_values = ft_matrix_create(sizeof(double), NUMBER_OF_HOGWARTS_COURSES,
			dataset->number_of_rows);
	i = dataset->number_of_rows - 1;
	elem = dataset->example_lst;
	while (elem)
	{
		example = *(const t_example **)elem->content;
		if (*example->value_array[1])
			house_index(example->value_array[1], i, gradient_descent->observed);
		course_values_add(input_values, i, example->double_value_array);
		elem = elem->next;
		if (elem && !i)
			FT_LOG_FATAL("Calculation error during "
				"setting up content of dataset!");
		i--;
	}
	gradient_descent->input_values = ft_matrix_normalize(input_values,
			E_DIR_ROW);
	ft_matrix_remove(&input_values);
	return ;
}

t_gradient_descent	*gradient_descent_initialize(
							const t_regression_type regression_type,
							const t_dataset *const dataset,
							const t_hyper_parameters *const hyper_parameters)
{
	t_gradient_descent		*gradient_descent;

	gradient_descent = ft_memalloc(sizeof(*gradient_descent));
	if (regression_type == E_LOGISTIC)
	{
		gradient_descent->observed = ft_matrix_create(sizeof(double),
				NUMBER_OF_HOGWARTS_HOUSES, dataset->number_of_rows);
		gradient_descent->weight = ft_matrix_create(sizeof(double),
				NUMBER_OF_HOGWARTS_HOUSES, NUMBER_OF_HOGWARTS_COURSES);
		gradient_descent->bias = ft_vector_create(sizeof(double),
				NUMBER_OF_HOGWARTS_HOUSES, E_DIR_ROW);
		gradient_descent->cost = ft_vector_create(sizeof(double),
				gradient_descent->observed->size.rows, E_DIR_ROW);
		gradient_descent->hyper_parameters = hyper_parameters;
		input_data_add(dataset, gradient_descent);
	}
	return (gradient_descent);
}
