# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 09:39:06 by user42            #+#    #+#              #
#    Updated: 2022/01/31 13:27:25 by arapaill         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC		=	gcc
CFLAGS =	-Wall -Wextra -Werror
SRC		=	srcs/ft_philo.c srcs/init.c srcs/philo_utils_1.c srcs/philo_utils_2.c \
			srcs/routine.c srcs/thread.c srcs/ft_stop.c
OBJ 	=	$(SRC:%.c=%.o)
NAME 	=	philo

all : $(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) ${SRC} -lpthread -o $(NAME)
			@echo "\n\033[32m[✓]\033[0m		[$(NAME) compiled]"

clean:
			@rm -f *.o
			@rm -f ./srcs/*.o

fclean:		clean
			@rm -f $(NAME)
			
re:			fclean all
		
.PHONY:		all clean fclean re