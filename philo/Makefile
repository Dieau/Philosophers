# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 11:04:41 by alakhdar          #+#    #+#              #
#    Updated: 2022/03/14 10:58:35 by alakhdar         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS		= 	src/main.c src/actions.c src/clear.c src/start.c src/routine.c src/utils.c
HEADER		=	includes/philo.h
OBJS		= ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -rf

all: ${NAME}

$(NAME) : ${SRCS} $(HEADER) Makefile
	@$(CC) $(CFLAGS) $(SRCS) -o ${NAME}
	@echo "\033[92m\n[- COMPILATION COMPLETE -]\n\033[0m"
	@echo "\033[94m\n[- PLEASE ENTER : -]\n\033[0m"
	@echo "\033[94m\n[- NUMBER OF PHILOSOPHERS -]\n\033[0m"
	@echo "\033[94m\n[- TIME TO DIE -]\n\033[0m"
	@echo "\033[94m\n[- TIME TO EAT -]\n\033[0m"
	@echo "\033[94m\n[- TIME TO SLEEP -]\n\033[0m"
	@echo "\033[94m\n[- NUMBER OF MEALS -]\n\033[0m"

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) ${NAME}
	$(RM) src/*.o
	@echo "\033[91m\n[- FILES DELETED -]\n\033[0m"

fclean : clean

re : fclean all

.PHONY : all clean bonus fclean re