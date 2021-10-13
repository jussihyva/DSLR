# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_cmd_variables.mk                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:50:47 by jkauppi           #+#    #+#              #
#    Updated: 2021/10/13 14:58:28 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifdef D
	DATASET			=	$(D)
else
	DATASET			=	"data/dataset_train.csv"
endif

ifdef L
	LEVEL			=	-L $(L)
else
	LEVEL			=	
endif

ifdef M
	MODE			=	$(M)
else
	MODE			=	TRAIN
endif

ifdef I
	ITERATIONS		=	-I $(I)
else
	ITERATIONS		=	-I 2000
endif
