/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:08:19 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/19 07:45:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static const t_vector	*output_vector_create(
									const size_t length,
									const t_list *const value_array_lst)
{
	t_vector		*vector;
	const t_list	*elem;
	const char		**value_array;
	const char		*house;
	size_t			i;

	vector = ft_vector_create(sizeof(double), length);
	i = 0;
	elem = value_array_lst;
	while (elem)
	{
		value_array = *(const char ***)elem->content;
		house = value_array[1];
		if (ft_strequ(house, "Gryffindor"))
		{
			((double **)vector->values)[i][0] = E_TRUE;
			FT_LOG_TRACE("House: %s", value_array[1]);
		}
		else
			((double **)vector->values)[i][0] = E_FALSE;
		i++;
		elem = elem->next;
	}
	return (vector);
}

static void	course_values_add(
						double *const course_values,
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
		ft_memcpy(&course_values[j], &value, sizeof(value));
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
	const t_list	*elem;
	const char		**value_array;
	size_t			i;

	matrix = ft_matrix_create(sizeof(double), number_of_rows,
			number_of_columns);
	i = 0;
	elem = value_array_lst;
	while (elem)
	{
		value_array = *(const char ***)elem->content;
		course_values_add(((double **const)matrix->values)[i], value_array);
		i++;
		elem = elem->next;
	}
	return (matrix);
}

const t_gradient_descent	*gradient_descent_initialize(
									const t_regression_type regression_type,
									const t_dataset *const dataset)
{
	const t_vector			*is_gryffindor_house;
	const t_matrix			*hogwarts_course_values;
	t_gradient_descent		*gradient_descent;
	t_vector				*weigth;

	gradient_descent = ft_memalloc(sizeof(*gradient_descent));
	if (regression_type == E_LOGISTIC)
	{
		is_gryffindor_house = output_vector_create(dataset->number_of_rows,
				dataset->value_array_lst);
		hogwarts_course_values = input_matrix_create(dataset->number_of_rows,
				NUMBER_OF_HOGWARTS_COURSES, dataset->value_array_lst);
		weigth = ft_vector_create(sizeof(double), NUMBER_OF_HOGWARTS_COURSES);
		gradient_descent->observed = is_gryffindor_house;
		gradient_descent->input_values = hogwarts_course_values;
		gradient_descent->weigth = weigth;
	}
	return (gradient_descent);
}
