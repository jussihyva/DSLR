# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_system.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:49:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/07 10:30:39 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS					=	$(shell uname -s)
CUR_DIR				=	$(abspath .)


SYSTEM_INCLUDE		=
ifeq ($(OS), Darwin)
	SYSTEM_INCLUDE	+=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1k/include
	SYSTEM_INCLUDE	+=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1l/include
	SYSTEM_INCLUDE	+=	-I $(HOME)/DSLR/DSLR/lib/libtensorflow/include/
endif
