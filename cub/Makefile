# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbenaali <bbenaali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/10 12:44:15 by slimane           #+#    #+#              #
#    Updated: 2025/08/22 11:07:32 by bbenaali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS= -Wall -Wextra -Werror -g3 -fsanitize=address
MLX_FLAG = -lmlx -framework OpenGL -framework AppKit

SRC=cub.c ft_help.c utils.c ft_destroy.c get_next_line.c parse_map.c ft_split.c ft_strjoin.c ft_substr.c ft_strtrim.c\
	parse.c get_next_line_utils.c init.c ft_clear.c ft_atoi.c ft_strlen.c
OBJ=${SRC:.c=.o} 

NAME=cub3D

all:run

run:${NAME} clean

${NAME}:${OBJ}
	${CC} ${CFLAGS} ${MLX_FLAG} ${OBJ} -o ${NAME}

%.o:%.c cub.h
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}


re: fclean all