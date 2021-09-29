# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mk_cmd_variables.mk                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:50:47 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/29 10:21:04 by jkauppi          ###   ########.fr        #
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
	MODE			=	L
endif
