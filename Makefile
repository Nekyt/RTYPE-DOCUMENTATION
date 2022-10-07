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
		Ecs/Entity/Entity.cpp \
		Ecs/Entity/EntityManager.cpp \
		Ecs/Component/ComponentManager.cpp \
		Ecs/Component/sources/Acceleration.cpp \
		Ecs/Component/sources/Position.cpp \
		Ecs/Component/sources/Speed.cpp \
		Ecs/Component/sources/Health.cpp \
		Ecs/Component/sources/Hitbox.cpp \
		Ecs/Component/sources/Text.cpp \
		Ecs/System/CollisionSystem.cpp \
		Ecs/System/MoveSystem.cpp \
		Ecs/System/GraphicSystem.cpp \
		Ecs/System/TextSystem.cpp \
		Ecs/System/SystemManager.cpp \
		Ecs/Manager.cpp \


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