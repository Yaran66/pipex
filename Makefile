# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: wjasmine <marvin@42.fr>                    +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/10/26 14:58:42 by wjasmine          #+#    #+#             #
#   Updated: 202#   Updated: 2022/02/12 19:38:24 by wjasmine         ###   ########.fr
      #************************************************************* #

NAME		=	pipex

SRCS		=	pipex.c ft_split.c ft_strjoin.c ft_strnstr.c ft_strlen.c

HEADER		=	pipex.h
OBJS		= 	${SRCS:%.c=%.o}

CC			= 	gcc
RM			= 	rm -f

 OPTFLAGS 	= 	-O2
CFLAGS		= 	-Wall -Wextra -Werror -I${HEADER}

.PHONY:			all clean fclean re

all:			${NAME}

${NAME}:		${OBJS}
				${CC} -o ${NAME} ${OBJS}

%.o	:			%.c ${HEADER} Makefile
				${CC} ${CFLAGS} ${OPTFLAGS}	-c $< -o $@


clean:
				${RM} ${OBJS}

fclean:			clean
				${RM} ${NAME}

re:				fclean all
