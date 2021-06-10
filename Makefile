##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CC	=	gcc

RM	=	rm -f

NAME	=	libmy_malloc$(HOSTTYPE).so

LINK	=	libmy_malloc.so

CFLAGS	=	-Wall -Wextra -fPIC -Iinclude -g

SRC	=	./Src/malloc.c	\
		./Src/free.c	\
		./Src/realloc.c	\

OBJ	=	$(SRC:.c=.o)  $(MAIN:.c=.o)

RED             =       \033[0;31m
GREEN           =       \033[0;32m
NC              =       \033[0m
GREY            =       \033[90m
BG_COLOR        =       \033[46m
BLUE            =       \e[34m
YELLOW          =       \e[93m
CYAN            =       \e[96m

$(NAME)	:	$(OBJ)
		@echo -e '${GREEN}Flags${NC}:${GREY} $(LDFLAGS) $(CFLAGS)${NC}'
		$(CC) $(CFLAGS) $(OBJ) -shared -o $(NAME)
		@rm Src/*.o
		@echo -e '${GREEN}COMPILED${NC}: ${CYAN}./$(LINK)${NC}'


all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all
.PHONY:	fclean clean all re
