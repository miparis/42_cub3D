# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/11 12:37:16 by miparis           #+#    #+#              #
#    Updated: 2025/05/30 12:22:48 by miparis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

MY_SOURCES = ft_isdigit.c \
	     ft_atoi.c \
	     ft_split.c \
	     ft_strlen.c \
	     ft_strlcpy.c \
	     ft_substr.c \
		 ft_free_things.c \
		 ft_calloc.c \
		 ft_memset.c \
		 ft_bzero.c \
		 ft_strchr.c \
		 ft_strncmp.c \
		 ft_strjoin.c \
		 ft_strcmp.c \
		 ft_strnstr.c \
		 ft_itoa.c \
		 get_next_line.c \
		 get_next_line_utils.c \

MY_OBJECTS =  $(MY_SOURCES:.c=.o) 

INCLUDE = libft.h

CFLAGS = -Wall -Werror -Wextra -g3

CC		= gcc

%.o:%.c
		@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) 

$(NAME): $(MY_OBJECTS) 
		@ar rcs $(NAME) $(MY_OBJECTS) 

clean:
		@rm -f $(MY_OBJECTS)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
