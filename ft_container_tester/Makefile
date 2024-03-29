# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 20:39:50 by mdoquocb          #+#    #+#              #
#    Updated: 2023/02/28 20:39:52 by mdoquocb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = ft_stl
PROJECT2 = stl

	#  BINARY  #

BIN_PATH = Bin/

BIN_NAME = $(PROJECT)

BIN = $(addprefix $(BIN_PATH),$(BIN_NAME))

BIN_NAME2 = $(PROJECT2)

BIN2 = $(addprefix $(BIN_PATH),$(BIN_NAME2))

	#  INCLUDES  #

INC_PATH = ../ft_stl

INC_FLAGS = -I $(INC_PATH)

INC_PATH2 = ./Include

INC_FLAGS += -I $(INC_PATH)

	#  SOURCES  #

SRC_PATH = Sources/

SRC_NAME = $(notdir $(wildcard Sources/*.cpp))

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

	#  OBJECTS  #

OBJ_PATH = $(BIN_PATH)Objects/

OBJ_NAME = $(SRC_NAME:.cpp=.o)

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
	
	#  FLAGS  #

CC = c++

CC_FLAGS = -std=c++98 -Wall -Wextra -Werror

CC_DEF = -D real

CL = rm -rf

LEAK = leaks -atExit --

LEAKS = valgrind --leak-check=full


	#  COLORS STR #

GREEN = "\x1b[32m""\x1b[M"

RED= "\x1b[31m""\x1b[M"

BLUE = "\x1b[34m""\x1b[M"

	#  COLORS  #

ENDCOL = \033[0m

REDS = \033[1;31m

YEL = \033[1;33m

ORG = \033[0;33m

GRN = \033[1;32m

DGRAY = \033[1;30m

BLU = \033[1;34m

	#  COMPILATION  #

all: $(BIN) $(BIN2)
		@echo $(GREEN) Compilation $(PROJECT) is completed !!

$(OBJ_PATH)%.o:$(SRC_PATH)%.cpp
		@$(CC) $(CC_FLAGS) $(INC_FLAGS) -c $< -o $@
		@echo $(BLUE) $(notdir $@) is created !!

$(BIN): title directory $(OBJ)
		@$(CC) $(OBJ) -o $(BIN)
		@echo $(BLUE) $(notdir $(BIN)) is created !!

$(BIN2): $(OBJ)
		@$(CC) $(OBJ) $(CC_DEF) -o $(BIN2)
		@echo $(BLUE) $(notdir $(BIN2)) is created !!

run:
		@$(LEAK) ./test.sh

unit:
		@cd ../ft_container_unit_test && ./start.sh

full: run unit

title: 
		@echo $(GREEN)******************$(PROJECT)******************

directory: 	
		@mkdir -p $(OBJ_PATH) > /dev/null 2>&1 || true
		@echo $(BLUE) Binary $(PROJECT) directory created !!


clean: 
		@$(CL) $(OBJ)
		@echo $(RED) Object $(notdir $(OBJ)) is delete !

fclean: clean 
		@$(CL) $(BIN) $(BIN2)
		@echo $(RED) Binary $(notdir $(BIN)) and $(notdir $(BIN2)) is delete !

finish: 
		@$(CL) $(BIN_PATH)
		@echo $(RED) All $(PROJECT) is delete !

re:	fclean all

.PHONY :	all clean fclean finish re directory title
