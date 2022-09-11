# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 14:08:26 by yjoo              #+#    #+#              #
#    Updated: 2022/09/11 20:37:49 by yjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = minishell

INCLUDE = -I./include
RLINC = -lreadline -L${HOME}/.brew/opt/readline/lib
SRCS_DIR = ./srcs
SRCS_FILES = main.c signal.c
PARSE_DIR = ./srcs/parse
PARSE_FILES = parse.c
SRCS = $(addprefix $(addsuffix /, $(SRCS_DIR)), $(SRCS_FILES))\
		$(addprefix $(addsuffix /, $(PARSE_DIR)), $(PARSE_FILES))
OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -I${HOME}/.brew/opt/readline/include -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		@make -C ./libft/
		@$(CC) $(INCLUDE) $(RLINC) $^ ./libft/libft.a -o $@
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
