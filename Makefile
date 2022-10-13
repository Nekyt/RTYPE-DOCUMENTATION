##
## EPITECH PROJECT, 2022
## undefined
## File description:
## Makefile
##

SRC	=	Client/main.cpp \
		Graphics/Events.cpp \
		Graphics/InitSfml.cpp \
		Ecs/Entity/Entity.cpp \
		Ecs/Entity/EntityManager.cpp \
		Ecs/Component/ComponentManager.cpp \
		Ecs/Component/sources/Acceleration.cpp \
		Ecs/Component/sources/Controlable.cpp \
		Ecs/Component/sources/Damage.cpp \
		Ecs/Component/sources/Health.cpp \
		Ecs/Component/sources/Hitbox.cpp \
		Ecs/Component/sources/Id.cpp \
		Ecs/Component/sources/Position.cpp \
		Ecs/Component/sources/Rotate.cpp \
		Ecs/Component/sources/Size.cpp \
		Ecs/Component/sources/Speed.cpp \
		Ecs/Component/sources/Sprite.cpp \
		Ecs/Component/sources/Text.cpp \
		Ecs/System/CollisionSystem.cpp \
		Ecs/System/MoveSystem.cpp \
		Ecs/System/GraphicSystem.cpp \
		Ecs/System/TextSystem.cpp \
		Ecs/System/EventsSystem.cpp \
		Ecs/System/SystemManager.cpp \
		Ecs/System/System.cpp \
		Ecs/Manager.cpp \
		Client/GameClient.cpp \


OBJ	=	$(SRC:.cpp=.o)

NAME =	r-type

CXXFLAGS	=	-lsfml-window -lsfml-graphics -lsfml-system -Wall -Wextra -std=c++17 -g

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