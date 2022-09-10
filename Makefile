# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 14:08:26 by yjoo              #+#    #+#              #
#    Updated: 2022/09/10 14:27:21 by yjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = minishell

INCLUDE = -I./include
SRCS_DIR = ./srcs 
SRCS_FILES = main.c
SRCS = $(addprefix $(addsuffix /, $(SRCS_DIR)), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		@make -C ./libft/
		$(CC) $(INCLUDE) $^ ./libft/libft.a -lreadline -o $@

re : fclean all

clean :
		make -C ./libft/ clean
		$(RM) $(OBJS)

fclean : clean
		make -C ./libft/ fclean
		$(RM) $(NAME)

norm : 
	norminette $(SRCS)

.PHONY: all re clean fclean
Hello wordl
