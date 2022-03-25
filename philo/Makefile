# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 14:48:13 by mlarra            #+#    #+#              #
#    Updated: 2022/03/25 11:49:55 by mlarra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME	=	philo

# SRC		=	main.c	ft_atoi.c

# SRC_DIR	=	src

# SOURSES	=	${addprefix ${SRC_DIR}/, ${SRC}}

# HEADER	=	${SRC_DIR}/philo.h

# OBJ_DIR	=	objects

# OBJ		=	${SOURCES:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

# CFLAGS	=	-Wall -Wextra -Werror

# CC		=	gcc

# RM		=	rm -f

# .PHONY	:	all	clean	fclean	re	bonus	norm	philo

# ${OBJ_DIR}/%.o	:	${SRC_DIR}/%.c	${HEADER}
# 	mkdir ${OBJ_DIR} 2> /dev/null || true
# 	${CC} ${CFLAGS} -c $< -o $@

# ${NAME}	:	${OBJ}
# 	${CC} ${CFLAGS} $^ -o ${NAME}

# all		:	${NAME}

# clean	:
# 	${RM} ${OBJ}
# 	@rmdir ${OBJ_DIR} 2> /dev/null || true

# fclean	:	clean
# 	${RM} ${NAME}

# re		:	fclean all

# norm	:
# 	norminette ${SOURCES} ${HEADER}

NAME	=	philo

SRC		=	main.c	ft_atoi.c

HEADER	=	philo.h

OBJ		=	${SRC:%.c=%.o}

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

RM		=	rm -f

.PHONY	:	all	clean	fclean	re	bonus	norm

%.o	:	%.c	${HEADER}
	${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJ}
	${CC} ${CFLAGS} $^ -o $@

all		:	${NAME}

clean	:
	${RM} ${OBJ}

fclean	:	clean
	${RM} ${NAME}

re		:	fclean all

norm	:
	norminette ${SOURCES} ${HEADER}