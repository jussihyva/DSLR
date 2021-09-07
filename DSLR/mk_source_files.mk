# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/07 10:47:03 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES				=	input_params.c usage_print.c dataset.c \
							ft_strsplit_ex.c
SRC_H_FILES				=	$(NAME).h
LOCAL_LIBS				=	libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS				=	
GLOBAL_LIB_FOLDERS		=	
ifeq ($(OS), Darwin)
	GLOBAL_LIBS			+=	libtensorflow.dylib
	GLOBAL_LIB_FOLDERS	+=	/Users/jkauppi/DSLR/DSLR/lib/libtensorflow
else
	GLOBAL_LIBS	+=	libm.a
endif
