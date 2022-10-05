# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 14:08:26 by yjoo              #+#    #+#              #
#    Updated: 2022/10/06 03:25:50 by siokim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = minishell
FSANI = -g3 -fsanitize=address

OS = $(shell uname -s)

ifeq ($(OS), Darwin)
	RLINC = -lreadline -L${HOME}/.brew/opt/readline/lib
	RLLIB = -I${HOME}/.brew/opt/readline/include
else
	RLINC = -lreadline
endif

INCLUDE = -I./include
SRCS_DIR = ./srcs
SRCS_FILES = main.c signal.c utils.c
PARSE_DIR = ./srcs/parse
PARSE_FILES = parse.c parse_utils.c token.c token2.c cmd.c
EXECVE_FILES = exec.c redirect.c fileIO.c execute_cmd.c pipex.c execute_bulitin.c
EXECVE_DIR = ./srcs/execve
BUILTIN_DIR = ./srcs/builtin
BUILTIN_FILES = env.c echo.c exit.c pwd.c unset.c export.c


SRCS = $(addprefix $(addsuffix /, $(SRCS_DIR)), $(SRCS_FILES))\
		$(addprefix $(addsuffix /, $(PARSE_DIR)), $(PARSE_FILES))\
		$(addprefix $(addsuffix /, $(BUILTIN_DIR)), $(BUILTIN_FILES))\
		$(addprefix $(addsuffix /, $(EXECVE_DIR)), $(EXECVE_FILES))
OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) $(RLLIB) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		@make -C ./libft/
		@$(CC) $(FSANI) $(INCLUDE) $^ $(RLINC) ./libft/libft.a -o $@
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
