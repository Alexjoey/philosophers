# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amylle <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 11:58:06 by amylle            #+#    #+#              #
#    Updated: 2024/02/27 14:42:07 by amylle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR	= ./src
INC_DIR	= ./inc
OBJ_DIR	= ./obj

SRCS	= ./src/main.c
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
CC		= cc
CFLAGS	= -Wextra -Wall -Werror
INCLUDE	= -Llibft -lft -I$(INC_DIR)
RM		= rm -rf
LIBFT	= libft/libft.a
MAKEFLAGS += --no-print-directory
NAME	= philo

#---------------------------Messages--------------------------------------------

BOLD_PURPLE	=	\033[1;35m

BOLD_CYAN	=	\033[1;36m

BOLD_YELLOW	=	\033[1;33m

NO_COLOR	=	\033[0m


all:	$(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@ 

$(LIBFT):
		@make -C ./libft

$(NAME):	$(OBJS) $(LIBFT)
				@echo Compiling $(NAME)
				@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

clean:	
				@echo "$(BOLD_YELLOW)Removing all object files and directories"
				$(RM) $(OBJ_DIR)
				@make fclean -C ./libft

fclean:
				@echo "$(BOLD_YELLOW)Removing binaries"
				$(RM) $(NAME) $(OBJ_DIR)
				@make fclean -C ./libft

re:			fclean all
