##
## EPITECH PROJECT, 2022
## undefined
## File description:
## Makefile
##

SRC	=	Client/main.cpp \
	Client/GameClient.cpp \
	Graphics/Events.cpp \
	Graphics/InitSfml.cpp \

OBJ	=	$(SRC:.cpp=.o)

NAME =	r-type

CXXFLAGS	=	-lsfml-window -lsfml-graphics -lsfml-system -Wall -Wextra

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ $(OBJ) -o $(NAME) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f *~

re:	fclean all clean

debug:	$(OBJ)
	gcc -Wall -g -o $(NAME) $(OBJ)

.PHONY:	all $(NAME) clean fclean re debug