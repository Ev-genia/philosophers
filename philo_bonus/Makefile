# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 14:48:13 by mlarra            #+#    #+#              #
#    Updated: 2022/06/27 15:35:26 by mlarra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

SRC		=	main_bonus.c	ft_check_bonus.c	ft_atoi_bonus.c\
			ft_print_bonus.c	ft_init_bonus.c	ft_sleep_bonus.c\
			ft_utils_bonus.c	ft_free_bonus.c	ft_itoa.c	ft_strlen.c\
			ft_strjoin.c

HEADER	=	philo_bonus.h

OBJ		=	${SRC:%.c=%.o}

CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=thread -g

CC		=	cc

RM		=	rm -f

.PHONY	:	all	clean	fclean	re	norm	#bonus

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