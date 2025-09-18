# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: boris <boris@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 13:20:26 by brandebr          #+#    #+#              #
#    Updated: 2024/06/16 13:51:18 by boris            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

INC_DIR	= include/
SRC_DIR = src/
OBJ_DIR = obj/

SRC = main.c parse_it.c ft_read_map.c flood_map.c movements.c\
	  upload_img.c exit.c position.c bonus.c bonus_bis.c enemies_parse.c\

# LIBS = -L./Libft -lft -L./ft_printf -lftprintf -L./mlx -lmlx -framework OpenGL \
	   -framework AppKit

LIBS = -L./Libft -lft -L./ft_printf -lftprintf -L./mlx -lmlx -lm -lX11 -lXext -lbsd

OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC = cc

FLAGS = -Wall -Wextra -Werror -g -I. -I./libft -I./ft_printf -fsanitize=address -fno-omit-frame-pointer

LIBFT = ./Libft/libft.a
LIBFT_DIR = ./Libft

FT_PRINTF = ./ft_printf/libftprintf.a
FT_PRINTF_DIR = ./ft_printf

MLX = ./mlx/libmlx.a
MLX_DIR = ./mlx

all: Makefile libs $(NAME)

# %.o: %.c so_long.h ./Libft/libft.h ./ft_printf/ft_printf.h Makefile
# 	$(CC) $(FLAGS) -c $< -o $@
$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile
	@mkdir -p $(OBJ_DIR)
	$(CC) -I $(INC_DIR) -c $< -o $@ $(FLAGS)

$(NAME): $(LIBFT) $(FT_PRINTF) $(MLX) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)

valgrind:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./so_long maps/some.ber

libs:
	@make -C $(LIBFT_DIR) bonus
	@make -C $(FT_PRINTF_DIR)
	@make -C $(MLX_DIR)

clean: 
	/bin/rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)
	make clean -C $(FT_PRINTF_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)
	make fclean -C $(FT_PRINTF_DIR)
	make clean -C $(MLX_DIR)

re: fclean all 

.PHONY: all clean fclean re libs
