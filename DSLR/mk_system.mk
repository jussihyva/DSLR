# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_system.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:49:38 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/01 15:27:51 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS					=	$(shell uname -s)
CUR_DIR				=	$(abspath .)


SYSTEM_INCLUDE		=
ifeq ($(OS), Darwin)
	SYSTEM_INCLUDE	+=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1k/include
	SYSTEM_INCLUDE	+=	-I $(HOME)/.brew/Cellar/openssl@1.1/1.1.1l/include
endif
