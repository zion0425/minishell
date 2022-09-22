# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 14:08:26 by yjoo              #+#    #+#              #
#    Updated: 2022/09/22 19:05:17 by siokim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = minishell
FSANI = -g3 -fsanitize=address

INCLUDE = -I./include
RLINC = -lreadline -L${HOME}/.brew/opt/readline/lib
SRCS_DIR = ./srcs
SRCS_FILES = main.c signal.c
PARSE_DIR = ./srcs/parse
PARSE_FILES = parse.c parse_utils.c	token.c
EXECVE_FILES = fileIO.c execve.c redirect.c 
EXECVE_DIR = ./srcs/execve


SRCS = $(addprefix $(addsuffix /, $(SRCS_DIR)), $(SRCS_FILES))\
		$(addprefix $(addsuffix /, $(PARSE_DIR)), $(PARSE_FILES))\
 		$(addprefix $(addsuffix /, $(EXECVE_DIR)), $(EXECVE_FILES))

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
		@echo "\033[32m"clean_complete"\033[0m"

fclean : clean
		@make -C ./libft/ fclean
		@$(RM) $(NAME)
		@echo "\033[32m"fclean_complete"\033[0m"

norm : 
	@norminette $(SRCS)
	@norminette ./include

.PHONY: all re clean fclean
