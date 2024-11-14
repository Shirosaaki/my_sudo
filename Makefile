##
## EPITECH PROJECT, 2024
## MAKE
## File description:
## make
##

NAME	=	my_sudo

SRC		=	main.c

OBJ		=	$(SRC:.c=.o)

all: $(OBJ)
	make -C lib/my
	gcc -o $(NAME) $(OBJ) -lpam -lpam_misc -lcap -L. -lmy

clean:
	make clean -C lib/my
	rm -f $(OBJ)

fclean: clean
	make fclean -C lib/my
	rm -f $(NAME)

re: fclean all

run: re
	./$(NAME)
