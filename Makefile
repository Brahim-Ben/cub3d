# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slimane <slimane@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/20 14:52:44 by slimane           #+#    #+#              #
#    Updated: 2025/09/20 19:52:56 by slimane          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS= -Wall -Wextra -Werror 
MLX_FLAG = -lmlx -framework OpenGL -framework AppKit

SRC_M = mandatory/cub.c mandatory/ft_help.c mandatory/utils.c mandatory/ft_destroy.c mandatory/get_next_line.c \
	mandatory/parse_map.c mandatory/ft_split.c mandatory/ft_strjoin.c mandatory/ft_substr.c mandatory/ft_strtrim.c \
	mandatory/parse.c mandatory/get_next_line_utils.c mandatory/init.c mandatory/ft_clear.c mandatory/ft_atoi.c \
	mandatory/ft_strlen.c mandatory/ft_utils_help.c mandatory/ft_help_parse.c mandatory/check_direction.c \
	mandatory/ray-casting.c mandatory/textures.c mandatory/first_cub.c mandatory/second_cub.c \
	mandatory/Third_cub.c mandatory/Fourth_cub.c mandatory/fifth_cub.c 

OBJ_M = ${SRC_M:.c=.o} 

SRC_B = bonus/cub_bonus.c bonus/ft_help_bonus.c bonus/utils_bonus.c bonus/ft_destroy_bonus.c bonus/get_next_line_bonus.c \
	bonus/parse_map_bonus.c bonus/ft_split_bonus.c bonus/ft_strjoin_bonus.c bonus/ft_substr_bonus.c bonus/ft_strtrim_bonus.c \
	bonus/parse_bonus.c bonus/get_next_line_utils_bonus.c bonus/init_bonus.c bonus/ft_clear_bonus.c bonus/ft_atoi_bonus.c \
	bonus/ft_strlen_bonus.c bonus/ft_utils_help_bonus.c bonus/ft_help_parse_bonus.c bonus/check_direction_bonus.c \
	bonus/ray-casting_bonus.c bonus/textures_bonus.c bonus/first_cub_bonus.c bonus/second_cub_bonus.c bonus/third_cub_bonus.c \
	bonus/Fourth_cub_bonus.c  bonus/fifth_cub_bonus.c bonus/sexth_cub_bonus.c bonus/seventh_cub_bonus.c

OBJ_B = ${SRC_B:.c=.o}

NAME = cub3D

all: ${NAME}

${NAME}: ${OBJ_M}
	${CC} ${CFLAGS} ${MLX_FLAG} ${OBJ_M} -o ${NAME}
	
%bonus.o:%bonus.c  bonus/cub_bonus.h
	${CC} ${CFLAGS} -c $< -o $@

	
%.o:%.c mandatory/cub.h
	${CC} ${CFLAGS} -c $< -o $@

bonus: ${OBJ_B}
	${CC} ${CFLAGS} ${MLX_FLAG} ${OBJ_B} -o ${NAME}




clean:
	rm -rf ${OBJ_M} ${OBJ_B}

fclean: clean
	rm -rf ${NAME}

re: fclean all
