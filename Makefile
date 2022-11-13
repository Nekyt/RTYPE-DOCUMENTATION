##
## EPITECH PROJECT, 2022
## undefined
## File description:
## Makefile
##

SRC	=	Network/NetworkServer.cpp \
		Network/NetworkRoom.cpp \
		Graphics/Events.cpp \
		Graphics/InitSfml.cpp \
		Ecs/Entity/Entity.cpp \
		Ecs/Entity/EntityManager.cpp \
		Ecs/Component/ComponentManager.cpp \
		Ecs/Component/sources/Acceleration.cpp \
		Ecs/Component/sources/Controlable.cpp \
		Ecs/Component/sources/Bullet.cpp \
		Ecs/Component/sources/Bonus.cpp \
		Ecs/Component/sources/Damage.cpp \
		Ecs/Component/sources/Health.cpp \
		Ecs/Component/sources/Hitbox.cpp \
		Ecs/Component/sources/Id.cpp \
		Ecs/Component/sources/Pattern.cpp \
		Ecs/Component/sources/Position.cpp \
		Ecs/Component/sources/Rotate.cpp \
		Ecs/Component/sources/Speed.cpp \
		Ecs/Component/sources/Sprite.cpp \
		Ecs/Component/sources/Text.cpp \
		Ecs/System/CollisionSystem.cpp \
		Ecs/System/EnemyShootSystem.cpp \
		Ecs/System/BonusSystem.cpp \
		Ecs/System/EventsSystem.cpp \
		Ecs/System/MoveSystem.cpp \
		Ecs/System/PatternSystem.cpp \
		Ecs/System/GraphicSystem.cpp \
		Ecs/System/TextSystem.cpp \
		Ecs/System/SystemManager.cpp \
		Ecs/System/System.cpp \
		Ecs/Manager.cpp \
		Ecs/Clock.cpp \
		server/GameInstance/GameServer.cpp \
		server/Server.cpp \
		server/main.cpp \

SRC2 = 	Client/GameClient.cpp \
		Client/main.cpp \
		Network/NetworkClient.cpp \
		Ecs/Clock.cpp Ecs/Manager.cpp \
		Ecs/System/System.cpp \
		Ecs/Entity/Entity.cpp \
		Ecs/System/EventsSystem.cpp \
		Ecs/System/GraphicSystem.cpp \
		Ecs/System/CollisionSystem.cpp \
		Ecs/System/SystemManager.cpp \
		Ecs/Component/sources/Acceleration.cpp \
		Ecs/Component/sources/Controlable.cpp \
		Ecs/Component/sources/Health.cpp \
		Ecs/Component/sources/Position.cpp \
		Ecs/Component/sources/Speed.cpp \
		Ecs/Component/sources/Text.cpp \
		Ecs/Component/sources/Bullet.cpp \
		Ecs/Component/sources/Damage.cpp \
		Ecs/Component/sources/Hitbox.cpp \
		Ecs/Component/sources/Pattern.cpp \
		Ecs/Component/sources/Rotate.cpp \
		Ecs/Component/sources/Sprite.cpp \
		Graphics/InitSfml.cpp \
		Graphics/Events.cpp \
		Ecs/Component/ComponentManager.cpp \
		Ecs/Entity/EntityManager.cpp \
		Ecs/System/TextSystem.cpp \
		Ecs/System/MoveSystem.cpp \
		Ecs/Component/sources/Bonus.cpp \

OBJ	=	$(SRC:.cpp=.o)

OBJ2	=	$(SRC2:.cpp=.o)

NAME =	r-type

NAME2 =	client


CXXFLAGS	=	-lsfml-network -lsfml-window -lsfml-graphics -lsfml-system -Wall -Wextra -std=c++17 -g

all:	$(NAME)

$(NAME):	$(OBJ) $(OBJ2)
	g++ $(OBJ) -o $(NAME) $(CXXFLAGS)
	g++ $(OBJ2) -o $(NAME2) $(CXXFLAGS)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ2)

fclean:	clean
	rm -f $(NAME)
	rm -f $(NAME2)
	rm -f *~

re:	fclean all clean

debug:	$(OBJ)
	gcc -Wall -g -o $(NAME) $(OBJ)

.PHONY:	all $(NAME) clean fclean re debug