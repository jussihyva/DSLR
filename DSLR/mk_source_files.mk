# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_source_files.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 12:38:32 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/02 11:21:18 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_C_FILES		=	input_params.c usage_print.c
SRC_H_FILES		=	$(NAME).h
LOCAL_LIBS		=	libft_addons.a libftprintf.a libft.a
GLOBAL_LIBS		=	
ifeq ($(OS), Darwin)
	GLOBAL_LIBS	+=	
else
	GLOBAL_LIBS	+=	
endif
