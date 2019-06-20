# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 18:12:26 by fsidler           #+#    #+#              #
#    Updated: 2019/06/18 16:24:32 by fsidler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_NM =		ft_nm
FT_OTOOL =	ft_otool

CC =	gcc
FLAGS =	-Wall -Wextra -Werror -MMD
#-pedantic

ifeq ($(DEBUG), yes)
	FLAGS += -DNMO_DEBUG #-fsanitize=address,undefined #-g
endif

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

INC_DIR =	includes
SRC_DIR =	sources
OBJ_DIR =	objs

CHILD_DIR = funk/32 \
			funk/64 \

SRC_COMMON =	endianness.c \
				funk/32/fat_arch_32.c \
				funk/32/header_32.c \
				funk/32/segment_32.c \
				funk/32/section_32.c \
				funk/32/section_32_main.c \
				funk/32/nlist_32.c \
				funk/32/nlist_32_main.c \
				funk/64/fat_arch_64.c \
				funk/64/header_64.c \
				funk/64/segment_64.c \
				funk/64/section_64.c \
				funk/64/section_64_main.c \
				funk/64/nlist_64.c \
				funk/64/nlist_64_main.c \
				funk/funk.c \
				logger.c \
				file_info.c \
				fat_arch.c \
				machop.c \

SRC_NM = 		symbol_list.c \
				symbol_type.c \
				nm_print.c \
				nm_sort.c \
				nm_exec.c \
				nm_main.c \
				$(SRC_COMMON)

SRC_OTOOL =		otool_print.c \
				otool_exec.c \
				otool_main.c \
				$(SRC_COMMON)

OBJ_NM =	$(addprefix $(OBJ_DIR)/, $(SRC_NM:.c=.o))
OBJ_OTOOL =	$(addprefix $(OBJ_DIR)/, $(SRC_OTOOL:.c=.o))

DPD_NM = 	$(addprefix $(OBJ_DIR)/, $(SRC_NM:.c=.d))
DPD_OTOOL =	$(addprefix $(OBJ_DIR)/, $(SRC_OTOOL:.c=.d))

Y =		"\033[33m"
B =		"\033[34m"
M =		"\033[35m"
X =		"\033[0m"
UP =	"\033[2A"
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
		@$(CC) $(FLAGS) -o $@ $^ -L $(LIBFT_DIR) -lft
		@echo ${B}[$(FT_NM)] compilation success${X}

$(FT_OTOOL): $(OBJ_OTOOL)
		@$(CC) $(FLAGS) -o $@ $^ -L $(LIBFT_DIR) -lft
		@echo ${Y}[$(FT_OTOOL)] compilation success${X}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@make $(CHILD_DIR)
		@$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@ 
		@echo ${M}compiling [$@]...${X}

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
