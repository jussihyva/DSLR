# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/13 14:50:52 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES				=	input_params.c usage_print.c dataset.c \
							ft_strsplit_ex.c ft_gettime.c \
							ft_strarray_print.c ft_strarray_trim.c \
							dataset_send_to_influxdb.c \
							influxdb_line.c influxdb_line_measurement_create.c \
							influxdb_line_group_create.c
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
