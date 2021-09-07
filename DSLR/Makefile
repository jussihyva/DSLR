# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/09 10:45:12 by jkauppi           #+#    #+#              #
#    Updated: 2021/09/07 11:01:59 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Application specific parameters
NAME			=	dslr
NAMES			=	$(NAME)

# Colours for printouts
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
GRAY			=	\033[1;30m
PURPLE			=	\033[0;35m
END				=	\033[0m

# Input parameters

include		mk_system.mk
include		mk_cmd_variables.mk
include		mk_source_files.mk

# Folders
LIB				=	lib
BIN				=	.
DATA			=	data
OBJ				=	obj
SRC				=	src
INCLUDE			=	include
TEST			=	test
DOC				=	doc
FOLDERS			=	$(LIB) $(BIN) $(DATA) $(OBJ) $(SRC) $(INCLUDE) $(TEST) \
					$(DOC)
INCLUDES		=	-I $(INCLUDE) -I $(LIB)

# C (Source code) and H (Header) files
LOCAL_LIB_FILES	=	$(addprefix $(LIB)/, $(LOCAL_LIBS))
LIB_FILES		=	$(addprefix -l , $(patsubst lib%.a, %, $(LOCAL_LIBS)))
LIB_FILES		+=	$(addprefix -l , $(patsubst lib%.dylib, %, $(GLOBAL_LIBS)))

# Path folders for H, C, O and APP files
H_FILES			=	$(addprefix $(INCLUDE)/, $(SRC_H_FILES))
C_FILES			=	$(addprefix $(SRC)/, $(SRC_C_FILES))
O_FILES			=	$(addprefix $(OBJ)/, $(patsubst %.c, %.o, $(SRC_C_FILES)))
APP_FILES		=	$(addprefix $(BIN)/, $(NAMES))
APP_C_FILES		=	$(addprefix $(SRC)/, $(patsubst %, %.c, $(NAMES)))

# Compiler and linking parameters
CC				=	clang
C_FLAGS			=	-g -Wall -Wextra -Werror $(INCLUDES) $(SYSTEM_INCLUDE)
LD_FLAGS		=	-std=gnu17 -L$(LIB) $(LIB_FILES) -L $(GLOBAL_LIB_FOLDERS)

ifeq ($(OS), Darwin)
	D_ATTRIBUTES	=	-D DARWIN
else
	D_ATTRIBUTES	=	
endif
LD_FLAGS			+=	$(D_ATTRIBUTES)

.PHONY: all
all: $(FOLDERS) $(H_FILES) $(APP_C_FILES) $(C_FILES) libraries $(APP_FILES)

$(APP_FILES): $(BIN)/%: $(SRC)/%.c $(H_FILES) $(O_FILES) Makefile
	@$(CC) -o $@ $< $(O_FILES) $(LD_FLAGS) $(C_FLAGS)
	@echo "Program $(GREEN)$@$(END) created!"

$(O_FILES): $(OBJ)/%.o: $(SRC)/%.c $(H_FILES) Makefile $(LOCAL_LIB_FILES)
	@$(CC) -c -o $@ $< $(C_FLAGS) $(D_ATTRIBUTES)
	@echo "File $(YELLOW)$<$(END) -> $(GREEN)$@$(END) compiled!"

$(FOLDERS):
	mkdir $@

$(APP_C_FILES):
	touch $@

$(C_FILES):
	touch $@

$(H_FILES):
	touch $@

.PHONY: libraries
libraries:
	@make --no-print-directory -C ${LIB}

.PHONY: libraries_re
libraries_re:
	@make -C ${LIB} re

.PHONY: libraries_norm
libraries_norm:
	-@make -C ${LIB} norm

.PHONY: run
run: all
ifeq ($(OS), Darwin)
	$(CUR_DIR)/$(BIN)/$(NAME) $(LEVEL) $(DATASET)
else
	$(CUR_DIR)/$(BIN)/$(NAME) $(LEVEL) $(DATASET)
endif

.PHONY: run_leaks
run_leaks: all
ifeq ($(OS), Darwin)
	$(CUR_DIR)/$(BIN)/$(NAME) $(LEVEL) -l $(DATASET)
else
	valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all \
	$(CUR_DIR)/$(BIN)/$(NAME) $(LEVEL) $(DATASET)
endif

.PHONY: clean
clean:
	@make --no-print-directory -C ${LIB} clean
	rm -f $(O_FILES)

.PHONY: fclean
fclean: clean
	@make -C ${LIB} fclean
	rm -f $(BIN)/$(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm: libraries_norm
ifeq ($(OS), Darwin)
	norminette-beta
else
	norminette
endif

