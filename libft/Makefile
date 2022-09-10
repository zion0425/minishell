# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 05:36:50 by yjoo              #+#    #+#              #
#    Updated: 2021/11/19 05:36:50 by yjoo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = ar rc
NAME = libft.a
SRCS = ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_striteri.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c
SRCS_BONUS = ft_lstadd_back.c\
		ft_lstadd_front.c\
		ft_lstclear.c\
		ft_lstdelone.c\
		ft_lstiter.c\
		ft_lstlast.c\
		ft_lstmap.c\
		ft_lstnew.c\
		ft_lstsize.c
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ = $(OBJS) $(OBJS_BONUS)
else
	OBJ = $(OBJS)
endif

all: $(NAME)

$(NAME) : $(OBJ)
		$(LIB) $@ $?

%.o : %.c
		$(CC) $(CFLAGS) -c $?

clean:
		rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
		rm -f $(NAME)

re: fclean all

bonus:
	make WITH_BONUS=1 all

.PHONY: all clean fclean re bonus
