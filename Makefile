# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/20 10:35:04 by ubuntu            #+#    #+#              #
#    Updated: 2021/10/19 13:09:58 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROGRAM					=	DSLR/dslr
SUB_FOLDERS				=	Docker DSLR
CUR_DIR					=	$(abspath .)
DOCKER_NAME				=	$(shell which docker)
DOCKER-COMPOSE_NAME		=	$(shell which docker-compose)
JUPYTER_NAME			=	$(shell which jupyter | egrep jupyter)
PYTHON_NUMPY_VER		=	$(shell pip3 list | egrep "^numpy ")
PYTHON_MATPLOTLIB_VER	=	$(shell pip3 list | egrep "^matplotlib ")

# Colours for printouts
RED						=	\033[0;31m
GREEN					=	\033[0;32m
YELLOW					=	\033[0;33m
GRAY					=	\033[1;30m
PURPLE					=	\033[0;35m
END						=	\033[0m

define DOCKER_NOT_INSTALLED_ERROR

	Docker is not installed:

		1. For Hive MAC's:	Download alexandregv/42toolbox (github) and run init_docker.sh
		2. For std linux env:	sudo apt-get install docker"

		
endef

define OPENSSL_ERROR

	OPENSSL is not installed:

		1. For Hive MAC's:	brew install openssl

		
endef

.PHONY: all
all:
	@echo "$(GRAY)"
	@echo "Docker                   : ${DOCKER_NAME}"
	@echo "Docker compose           : ${DOCKER-COMPOSE_NAME}"
	@echo "Jupyter                  : ${JUPYTER_NAME}"
	@echo "Python numpy ver         : ${PYTHON_NUMPY_VER}"
	@echo "Python matplotlib ver    : ${PYTHON_MATPLOTLIB_VER}"
	@echo "$(END)"
	@echo ""
	@echo "$(GREEN)"
	@echo "1. Installation"	
	@echo "  make build"
	@echo ""
	@echo "2. Run the program"
	@echo "  make run"
	@echo ""
	@echo "3. Help"	
	@echo "  $(CUR_DIR)/${PROGRAM} -h"
	@echo "$(END)"
	@echo ""

.PHONY: help
help: all
	@echo "DONE"

$(PROGRAM): build

.PHONY: build
build: check_openssl check_docker $(SUB_FOLDERS) folders check_jupyter
	@echo "$(GREEN)"
	@echo "DONE"
	@echo "$(END)"

.PHONY: run
run:
	make -C DSLR run

$(SUB_FOLDERS):
	mkdir $@

.PHONY: folders
folders:
	@echo "$(PURPLE)"
	@echo "Compile sub folders:"
	@for folder in $(SUB_FOLDERS) ; do \
		echo "$(PURPLE)" ; \
		echo "  $$folder" ; \
		echo "$(END)" ; \
		make -C $$folder ; \
	done
	@echo "$(END)"

.PHONY: clean
clean:
	for folder in $(SUB_FOLDERS) ; do \
		make -C $$folder clean ; \
	done

.PHONY: fclean
fclean:
	for folder in $(SUB_FOLDERS) ; do \
		make -C $$folder fclean ; \
	done

.PHONY: re
re: all
	for folder in $(SUB_FOLDERS) ; do \
		make -C $$folder re ; \
	done

.PHONY: norm
norm:
	for folder in $(SUB_FOLDERS) ; do \
		make -C $$folder norm ; \
	done

.PHONY: check_docker
check_docker:
ifeq (, $(DOCKER_NAME))
	$(error $(DOCKER_NOT_INSTALLED_ERROR))
else ifeq (, $(DOCKER-COMPOSE_NAME))
	$(error $(DOCKER_NOT_INSTALLED_ERROR))
endif

.PHONY: check_openssl
check_openssl:

.PHONY: check_jupyter
check_jupyter:
ifeq (, $(JUPYTER_NAME))
	pip3 install notebook
endif
ifeq (, $(PYTHON_NUMPY_VER))
	pip3 install numpy
endif
ifeq (, $(PYTHON_MATPLOTLIB_VER))
	pip3 install matplotlib
endif
	jupyter notebook
