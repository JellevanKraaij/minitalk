# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jvan-kra <jvan-kra@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/19 15:45:22 by jvan-kra      #+#    #+#                  #
#    Updated: 2022/01/25 17:49:50 by jvan-kra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRV_NAME 	=	server
CLT_NAME	=	client
LIBFT		=	libft/libft.a
CFLAGS 		=	-Wall -Wextra -Werror
CC			= 	gcc
SRV_SRCS	=	main.c \
				ft_bzero.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c 
CLT_SRCS	=	main.c \
				ft_putstr_fd.c \
				ft_atoi_p.c \
				ft_bzero.c


_SRV_SRCS	= ${addprefix server_srcs/, ${SRV_SRCS}}
_CLT_SRCS	= ${addprefix client_srcs/, ${CLT_SRCS}}
SRV_OBJS	= ${_SRV_SRCS:.c=.o}
CLT_OBJS	= ${_CLT_SRCS:.c=.o}

all: ${SRV_NAME} ${CLT_NAME}

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

${SRV_NAME}: ${SRV_OBJS}
	${CC} ${SRV_OBJS} -o ${SRV_NAME}
${CLT_NAME}: ${CLT_OBJS}
	${CC} ${CLT_OBJS} -o ${CLT_NAME}


clean:
	${RM} ${SRV_OBJS} ${CLT_OBJS}

fclean: clean
	${RM} ${SRV_NAME} ${CLT_NAME}

re: fclean all

bonus: all

.PHONY: all clean fclean re