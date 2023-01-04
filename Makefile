# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/21 16:41:10 by pmeising          #+#    #+#              #
#    Updated: 2023/01/04 14:10:56 by pmeising         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= cub3D

INC_DIR		:= inc/

CC			:= gcc

CFLAGS		:= -Werror -Wextra -Wall -g -I $(INC_DIR)

DEBUG		:= -fsanitize=address

RM			:= rm -f

MLX_DIR		:= ./minilibx-linux/

MLX			:= ./minilibx-linux/libmlx.a

SRC_DIR		:= ./src/

OBJ_DIR		:= ./obj/

LIBFT_DIR	:= ./libft_lib

LIBFT		:= libft_lib/libft.a

OS			:= $(shell uname)

ifeq ($(OS),Darwin)
	COMPILE = $(CC) $(CFLAGS) $(LIBFT) ${READLINE} $^ -o $@
else
	COMPILE = $(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -L/usr/X11/lib -lXext -lX11 -o $(NAME)
endif

SRC			:=	${SRC_DIR}main.c \
				${SRC_DIR}ft_hooks.c \
				${SRC_DIR}ft_parsing.c \
				${SRC_DIR}ft_parsing_2.c \
				${SRC_DIR}ft_free_funcs.c \
				${SRC_DIR}ft_check_map.c \
				${SRC_DIR}ft_check_map_2.c \
				${SRC_DIR}ft_raycast.c \
# makefile starts here
all: $(NAME)

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(MLX):
			make -C $(MLX_DIR)

# create obj directory ($@ represents name of target/rule)
$(OBJ_DIR):
			@mkdir $@

$(OBJ): | $(OBJ_DIR)

# compiles .c files into .o files and puts them into /obj directory ($< represents first prerequisite required) 
$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
		$(CC) $(CFLAGS) -c $< -o $@
		
# compiles the object files and creates the executable
# $^ : name of prerequisite/dependency that caused the rule/target (=whole thing) to execute
$(NAME):	$(OBJ)
			$(MAKE) bonus -C $(LIBFT_DIR)
			$(COMPILE)
			
# remove all object files and also clean libft
clean:
		$(MAKE) clean -C $(LIBFT_DIR)
		rm -f $(OBJ)

# same as clean but also removes the executable
fclean: clean
	$(MAKE) clean -C $(LIBFT_DIR)
		rm -f $(NAME)
		rmdir $(OBJ_DIR)

# make the whole compilation from scratch
re: fclean all

# prevents rules and files with potentially same names being mixed up
.PHONY = all clean fclean re
