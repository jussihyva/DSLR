/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:08:19 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/02 22:12:57 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static size_t	house_index(
					const char *const hogwarts_house,
					t_vector_size *i,
					double **matrix_values)
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
		i->rows = index;
		matrix_values[i->rows][i->columns] = E_TRUE;
		FT_LOG_TRACE("House: %s", hogwarts_house);
	}
	else
		FT_LOG_WARN("Unknown house: %s", hogwarts_house);
	return (index);
}

static const t_matrix	*output_vector_create(
									const size_t length,
									const t_list *const value_array_lst)
{
	t_matrix		*matrix;
	const t_list	*elem;
	const char		**value_array;
	t_vector_size	i;
	int				index;

	matrix = ft_matrix_create(sizeof(double), NUMBER_OF_HOGWARTS_HOUSES,
			length);
	i.columns = length - 1;
	elem = value_array_lst;
	while (elem)
	{
		value_array = *(const char ***)elem->content;
		if (*value_array[1])
			index = house_index(value_array[1], &i, (double **)matrix->values);
		i.columns--;
		elem = elem->next;
	}
	return (matrix);
}

static void	course_values_add(
						double **const course_values,
						const size_t column,
						const char **const value_array)
{
	size_t		i;
	size_t		j;
	char		*endptr;
	double		value;

	j = 0;
	i = 5;
	while (++i < 19)
	{
		value = strtod(value_array[i], &endptr);
		course_values[j][column] = value;
		j++;
	}
	return ;
}

static const t_matrix	*input_matrix_create(
									const size_t number_of_rows,
									const size_t number_of_columns,
									const t_list *const value_array_lst)
{
	t_matrix		*matrix;
	const t_matrix	*matrix_normalized;
	const t_list	*elem;
	const char		**value_array;
	size_t			i;

	matrix = ft_matrix_create(sizeof(double), number_of_columns,
			number_of_rows);
	i = number_of_rows - 1;
	elem = value_array_lst;
	while (elem)
	{
		value_array = *(const char ***)elem->content;
		course_values_add((double **const)matrix->values, i, value_array);
		elem = elem->next;
		if (elem && !i)
			FT_LOG_FATAL("Calculation error during "
				"setting up content of dataset!");
		i--;
	}
	matrix_normalized = ft_matrix_normalize(matrix, E_DIR_ROW);
	ft_matrix_remove(&matrix);
	return (matrix_normalized);
}

t_gradient_descent	*gradient_descent_initialize(
									const t_regression_type regression_type,
									const t_dataset *const dataset)
{
	t_gradient_descent		*gradient_descent;

	gradient_descent = ft_memalloc(sizeof(*gradient_descent));
	if (regression_type == E_LOGISTIC)
	{
		gradient_descent->observed = output_vector_create(
				dataset->number_of_rows, dataset->value_array_lst);
		gradient_descent->input_values
			= input_matrix_create(dataset->number_of_rows,
				NUMBER_OF_HOGWARTS_COURSES, dataset->value_array_lst);
		gradient_descent->weight = ft_matrix_create(sizeof(double),
				NUMBER_OF_HOGWARTS_HOUSES, NUMBER_OF_HOGWARTS_COURSES);
		gradient_descent->bias = ft_vector_create(sizeof(double),
				NUMBER_OF_HOGWARTS_HOUSES, E_DIR_ROW);
		gradient_descent->cost = ft_vector_create(sizeof(double),
				gradient_descent->observed->size.rows, E_DIR_ROW);
	}
	return (gradient_descent);
}
