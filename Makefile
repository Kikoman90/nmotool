# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 18:12:26 by fsidler           #+#    #+#              #
#    Updated: 2019/05/24 18:21:14 by fsidler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_NM =		ft_nm
FT_OTOOL =	ft_otool

CC =	gcc
FLAGS =	-Wall -Wextra -Werror #-pedantic

ifeq ($(DEBUG),yes)
	FLAGS += -g -fsanitize=address,undefined -D DEBUG
endif

INC_DIR =	includes
SRC_DIR =	sources
OBJ_DIR =	objs

SRC_COMMON =	file.c \
				endian.c \
				string.c \
				log.c \

SRC_NM = 		nm.c \
				$(SRC_COMMON)

SRC_OTOOL =		otool.c \
				$(SRC_COMMON)

OBJ_NM =	$(addprefix $(OBJ_DIR)/, $(SRC_NM:.c=.o))
OBJ_OTOOL =	$(addprefix $(OBJ_DIR)/, $(SRC_OTOOL:.c=.o))

Y =		"\033[33m"
B =		"\033[34m"
M =		"\033[35m"
X =		"\033[0m"
UP =	"\033[A"
CUT =	"\033[K"

all:
		@make -j $(FT_NM)
		@make -j $(FT_OTOOL)

debug\ $(FT_NM):
		@make -j $(FT_NM) DEBUG=yes

debug\ $(FT_OTOOL):
		@make -j $(FT_OTOOL) DEBUG=yes

debug:
		@make -debug ft_nm
		@make -debug ft_otool

$(FT_NM): $(OBJ_NM)
		@$(CC) $(FLAGS) -I $(INC_DIR) $^ -o $@
		@echo ${B}[$(FT_NM)] compilation success

$(FT_OTOOL): $(OBJ_OTOOL)
		@$(CC) $(FLAGS) -I $(INC_DIR) $^ -o $@
		@echo ${Y}[$(FT_OTOOL)] compilation success

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@echo ${M}compiling [$@]...${X}
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@
		@printf ${UP}${CUT}

clean:
		@rm -rf $(OBJ_DIR)

fclean: clean
		@rm -f $(FT_NM)
		@rm -f $(FT_OTOOL)

re:
		@make fclean
		@make

.PHONY: all clean fclean re
