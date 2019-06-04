# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 18:12:26 by fsidler           #+#    #+#              #
#    Updated: 2019/06/04 15:56:47 by fsidler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_NM =		ft_nm
FT_OTOOL =	ft_otool

CC =	gcc
FLAGS =	-Wall -Wextra -Werror -MMD
#-pedantic

ifeq ($(DEBUG), yes)
	FLAGS += -DNMO_DEBUG #-g -fsanitize=address,undefined
endif

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

INC_DIR =	includes
SRC_DIR =	sources
OBJ_DIR =	objs

CHILD_DIR = funk

SRC_COMMON =	funk/fat_arch_funk.c \
				funk/header_funk.c \
				funk/segment_funk.c \
				funk/section_funk.c \
				funk/nlist_funk1.c \
				funk/nlist_funk2.c \
				funk/funk1.c \
				funk/funk2.c \
				machop.c \
				fileinf.c \
				endianness.c \
				logger.c \

SRC_NM = 		nm.c \
				symbol_table.c \
				$(SRC_COMMON)

SRC_OTOOL =		otool.c \
				$(SRC_COMMON)

OBJ_NM =	$(addprefix $(OBJ_DIR)/, $(SRC_NM:.c=.o))
OBJ_OTOOL =	$(addprefix $(OBJ_DIR)/, $(SRC_OTOOL:.c=.o))

DPD_NM = 	$(addprefix $(OBJ_DIR)/, $(SRC_NM:.c=.d))
DPD_OTOOL =	$(addprefix $(OBJ_DIR)/, $(SRC_OTOOL:.c=.d))

Y =		"\033[33m"
B =		"\033[34m"
M =		"\033[35m"
X =		"\033[0m"
UP =	"\033[A"
CUT =	"\033[2K"

all:
		@make -C $(LIBFT_DIR) all
		@make -j $(FT_NM)
		@make -j $(FT_OTOOL)

debug:
		@make -C $(LIBFT_DIR) all
		@make $(FT_NM) DEBUG=yes
		@make $(FT_OTOOL)

$(CHILD_DIR):
		@mkdir -p $(OBJ_DIR)/$@

$(FT_NM): $(OBJ_NM)
		$(CC) $(FLAGS) -o $@ $(OBJ_NM) -L $(LIBFT_DIR) -lft
		@echo ${B}[$(FT_NM)] compilation success${X}

$(FT_OTOOL): $(OBJ_OTOOL)
		$(CC) $(FLAGS) -o $@ $(OBJ_OTOOL) -L $(LIBFT_DIR) -lft
		@echo ${Y}[$(FT_OTOOL)] compilation success${X}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@make $(CHILD_DIR)
		@echo ${CUT} ${M}compiling [$@]...${X} ${UP}
		$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@ 

norme:
		@make norme -C $(LIBFT_DIR)
		@echo
		norminette ./$(INC_DIR)
		@echo
		norminette ./$(SRC_DIR)

clean:
		@make clean -C $(LIBFT_DIR)
		@rm -rf $(OBJ_DIR)

fclean:
		@make fclean -C $(LIBFT_DIR)
		@rm -rf $(OBJ_DIR)
		@rm -f $(FT_NM)
		@rm -f $(FT_OTOOL)

re:
		@make fclean
		@make

.PHONY: all debug norme clean fclean re

-include $(DPD_NM)
-include $(DPD_OTOOL)
