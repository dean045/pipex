# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 17:34:58 by brhajji-          #+#    #+#              #
#    Updated: 2022/03/01 15:25:17 by brhajji-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs/
SRCS = ft_printf.c ft_putstr_fd.c ft_putnbr_fd.c\
	   ft_putnbr_base.c ft_putchar_fd.c
OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a
CC = gcc
RM = rm -f
.c.o:	
	${CC} -Wall -Wextra -Werror -c $< -o ${<:.c=.o}
${NAME}: ${OBJS}	
	ar rc ${NAME} ${OBJS}
all : ${NAME}
test : 	
clean :
	${RM} ${OBJS} ${BONUSOBJ}
fclean : clean	
	${RM} ${NAME} 
re : fclean all
.PHONY : all clean fclean re
