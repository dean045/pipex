# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brhajji- <brhajji-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 17:34:58 by brhajji-          #+#    #+#              #
#    Updated: 2022/03/04 16:24:18 by brhajji-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR = ./srcs

SRCS	= main.c error.c ft_split.c ft_strjoin.c parsing.c pipex.c

PRINTF_DIR = /printf

OBJS			=	$(addprefix $(SRC_DIR)/, $(SRCS:%.c=%.o))

NAME			=	pipex

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -g3

RM				=	rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
	cd printf && make
	$(CC) -o $(NAME) $(OBJS) printf/libftprintf.a

all:		${NAME}

bonus :		$(BONUS)	
				rm -f $(NAME)

clean:	
	cd printf && make clean	
	${RM} ${OBJS}

fclean:		clean			
		${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re
