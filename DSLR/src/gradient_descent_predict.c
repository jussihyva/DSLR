/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_descent_predict.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 09:00:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/10/24 17:05:48 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

static void	create_result_file(const t_vector *const predicted_argmax)
{
	char		write_buf[WRITE_BUF_SIZE];
	size_t		i;
	size_t		house_id;
	const char	*houses_file;
	int			fd;

	houses_file = ft_file_path_create(HOUSES_RESULT_FILE_NAME);
	remove(houses_file);
	fd = open(houses_file, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	i = -1;
	ft_sprintf(write_buf, "Index,Hogwarts House\n");
	write(fd, write_buf, ft_strlen(write_buf));
	while (++i < predicted_argmax->size.rows)
	{
		house_id = (int)((double **)predicted_argmax->values)[i][0];
		ft_sprintf(write_buf, "%lu,%s\n", i, g_hogwarts_house_array[house_id]);
		write(fd, write_buf, ft_strlen(write_buf));
	}
	close(fd);
	ft_strdel((char **)&houses_file);
	return ;
}

void	gradient_descent_predict(
						t_gradient_descent *const gradient_descent)
{
	const t_matrix		*predicted;
	const t_matrix		*predicted_transposed;
	const t_vector		*predicted_argmax;

	weight_bias_read(gradient_descent->weight, gradient_descent->bias);
	predicted = predict(gradient_descent->input_values,
			gradient_descent->bias, gradient_descent->weight);
	predicted_transposed = ft_matrix_transpose(predicted);
	predicted_argmax = ft_matrix_argmax(predicted_transposed, E_DIR_ROW);
	create_result_file(predicted_argmax);
	if (ft_log_get_level() <= LOG_DEBUG)
		ft_matrix_print("PREDICTED", predicted_transposed, E_DOUBLE);
	prediction_validate(gradient_descent->observed, predicted_argmax);
	ft_matrix_remove((t_matrix **)&predicted_argmax);
	ft_matrix_remove((t_matrix **)&predicted_transposed);
	ft_matrix_remove((t_matrix **)&predicted);
	return ;
}
