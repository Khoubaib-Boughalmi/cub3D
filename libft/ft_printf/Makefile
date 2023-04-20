NAME = libftprintf.a
CC = gcc
flags = -Wall -Wextra -Werror
ar = ar rcs
RM = rm -f

SRCS =		ft_printf.c  \
				ft_printf_utils.c \
				ft_puthex.c \
				ft_putnbr.c \

OBJS = ${SRCS:.c=.o}

%.o:%.c
		${CC} -c $< -o $@ ${flags}

${NAME} : ${OBJS}
			${ar} ${NAME} ${OBJS}

all : ${NAME}

clean :
				${RM} ${OBJS}
fclean :clean
				${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
