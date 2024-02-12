NAME = libftprintf.a
CC = cc
RM = rm -f
FLAG = -Wall -Wextra -Werror
SRC = 	./ft_printf.c

OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME):
	${CC} $(FLAG) -c $(SRC)
	ar rc $(NAME) ${OBJ}
clean:
	${RM}  ${OBJ}
fclean: clean
	${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re