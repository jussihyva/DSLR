# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/07 22:23:38 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES				=	input_params.c usage_print.c dataset.c \
							ft_strsplit_ex.c
SRC_H_FILES				=	$(NAME).h
LOCAL_LIBS				=	libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS				=	libssl.a libcrypto.a libtensorflow.a
GLOBAL_LIB_FOLDERS		=	
ifeq ($(OS), Darwin)
	GLOBAL_LIBS			+=	
	GLOBAL_LIB_FOLDERS	+=	$(HOME)/lib/libtensorflow
	GLOBAL_LIB_FOLDERS	+=	$(HOME)/.brew/Cellar/openssl@1.1/1.1.1k/lib
else
	GLOBAL_LIBS	+=	libm.a
endif
