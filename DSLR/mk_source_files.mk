# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/26 23:39:20 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES				=	input_params.c usage_print.c dataset.c \
							ft_strsplit_ex.c ft_gettime.c \
							ft_strarray_print.c ft_strarray_trim.c \
							dataset_send_to_influxdb.c \
							influxdb_line.c influxdb_line_measurement_create.c \
							influxdb_line_group_create.c \
							influxdb_line_tags.c \
							gradient_descent.c gradient_descent_iteration.c \
							ft_matrix_create.c ft_vector_create.c \
							ft_matrix_dot_matrix.c \
							ft_matrix_dot_vector_double.c \
							ft_matrix_transpose.c ft_vector_transpose.c \
							ft_vector_add_double.c ft_matrix_add_double.c \
							ft_matrix_add_vector.c ft_matrix_exp_double.c \
							ft_matrix_add_matrix.c \
							ft_vector_add_vector.c ft_matrix_log.c \
							ft_vector_div_double.c ft_double_div_vector.c \
							ft_matrix_print.c ft_vector_print.c \
							residual.c ft_matrix_subtract_matrix.c \
							ft_matrix_multiply_matrix.c \
							ft_matrix_sum.c ft_vector_abs_double.c \
							ft_shape_print.c cost.c ft_double_subtract_matrix.c
							# train.c
SRC_H_FILES				=	$(NAME).h
LOCAL_LIBS				=	libft_addons.a libftprintf.a libft.a
# GLOBAL_LIBS				=	libssl.a libcrypto.a libtensorflow.a
GLOBAL_LIBS				=	libssl.a libcrypto.a
GLOBAL_LIB_FOLDERS		=	
ifeq ($(OS), Darwin)
	GLOBAL_LIBS			+=	
	GLOBAL_LIB_FOLDERS	+=	$(HOME)/lib/libtensorflow
	GLOBAL_LIB_FOLDERS	+=	$(HOME)/.brew/Cellar/openssl@1.1/1.1.1k/lib
else
	GLOBAL_LIBS	+=	libm.a
endif
