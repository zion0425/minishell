# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 14:08:26 by yjoo              #+#    #+#              #
#    Updated: 2022/09/10 18:59:47 by siokim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = minishell

INCLUDE = -I./include
SRCS_DIR = ./srcs 
SRCS_FILES = main.c execve.c
SRCS = $(addprefix $(addsuffix /, $(SRCS_DIR)), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		@make -C ./libft/
		@$(CC) $(INCLUDE) $^ ./libft/libft.a -lreadline -o $@
		@echo "\033[32m"minishell_complete"\033[0m"

re : fclean all

clean :
		@make -C ./libft/ clean
		@$(RM) $(OBJS)

fclean : clean
		@make -C ./libft/ fclean
		@$(RM) $(NAME)

norm : 
	norminette $(SRCS)

.PHONY: all re clean fclean
