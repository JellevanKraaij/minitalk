# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jvan-kra <jvan-kra@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2021/10/19 15:45:22 by jvan-kra      #+#    #+#                  #
#    Updated: 2022/01/19 15:12:53 by jvan-kra      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRV_NAME 	=	server
CLT_NAME	=	client
LIBFT		=	libft/libft.a
CFLAGS 		=	-g -Wall -Wextra

SRV_SRCS	=	main.c \
				ft_printf/ft_printf.c \
				ft_printf/ft_printf_char.c \
				ft_printf/ft_printf_hex.c \
				ft_printf/ft_printf_num.c \
				ft_printf/ft_printf_str.c \
				ft_printf/ft_writers.c \
				ft_printf/ft_helpers.c
CLT_SRCS	=	main.c


_SRV_SRCS	= ${addprefix server_srcs/, ${SRV_SRCS}}
_CLT_SRCS	= ${addprefix client_srcs/, ${CLT_SRCS}}
SRV_OBJS	= ${_SRV_SRCS:.c=.o}
CLT_OBJS	= ${_CLT_SRCS:.c=.o}

all: ${SRV_NAME} ${CLT_NAME}

%.o: %.c
	${CC} ${CFLAGS} -Ilibft -c -o $@ $<

${LIBFT}:
	@${MAKE} -C libft

${SRV_NAME}: ${LIBFT} ${SRV_OBJS}
	${CC} ${SRV_OBJS} ${LIBFT} -o ${SRV_NAME}
${CLT_NAME}: ${LIBFT} ${CLT_OBJS}
	${CC} ${CLT_OBJS} ${LIBFT} -o ${CLT_NAME}


clean:
	@${MAKE} -C libft clean
	${RM} ${SRV_OBJS} ${CLT_OBJS}

fclean: clean
	@${MAKE} -C libft fclean
	${RM} ${SRV_NAME} ${CLT_NAME}

re: fclean all

bonus: all

.PHONY: all clean fclean re