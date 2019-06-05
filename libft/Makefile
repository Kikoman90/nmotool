# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/02 11:09:55 by fsidler           #+#    #+#              #
#    Updated: 2019/06/05 18:43:07 by fsidler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -MMD

DIR_SRCS = sources

DIR_OBJS = objs

HEADERS = includes

SRCS = 	ft_toupper.c \
		ft_strlen.c \
		ft_bzero.c \
		ft_itoa.c \
		ft_strnew.c \
		ft_strcat.c \
		ft_strcpy.c \
		ft_putchar.c \
		ft_putstr.c \
	  	ft_putendl.c \
	  	ft_strjoin.c \
		ft_strcmp.c \

OBJS = $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.o))
DPDS = $(addprefix $(DIR_OBJS)/, $(SRCS:.c=.d))

all: tmp $(NAME)

$(NAME): $(OBJS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)
		@echo "\033[37m[$(NAME)] compilation success"

tmp:
		@mkdir -p $(DIR_OBJS)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
		@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

norme:
		norminette ./$(HEADERS)
		@echo
		norminette ./$(DIR_SRCS)

clean:
		@rm -f $(OBJ)
		@rm -rf $(DIR_OBJS)

fclean:	clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all, tmp, norme, clean, fclean, re

-include $(DPDS)
