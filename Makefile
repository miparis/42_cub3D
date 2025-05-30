# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 12:10:09 by miparis           #+#    #+#              #
#    Updated: 2025/05/30 12:46:48 by miparis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -Iincludes -Iincludes/libft -Iincludes/minilibx-linux
LIBFT_DIR	= includes/libft
MLX_DIR		= includes/minilibx-linux
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
LIBS		= $(LIBFT) $(MLX) -lm

MY_SOURCES	= src/main.c

OBJS		= ${MY_SOURCES:.c=.o}

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# =================== COMPILACIÓN GENERAL =================== #

all: $(NAME)

$(LIBFT):
	@echo "📚 Compiling libft..."
	@$(MAKE) -s -C $(LIBFT_DIR) > /dev/null

$(MLX):
	@echo "🖼️ Compiling mlx..."
	@$(MAKE) -s -C $(MLX_DIR) > /dev/null 2>&1

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)
	@echo "✅ Cub3D operating."

# =================== LIMPIEZA =================== #

clean:
	@rm -f $(OBJS)
	@$(MAKE) -s -C $(LIBFT_DIR) clean  > /dev/null
	@$(MAKE) -s -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "🧹 Objects clean..."


fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@rm -f $(MLX)
	@echo "🧹 All cleaned up!"

re: fclean all

.PHONY: all clean fclean re
