cmake_minimum_required (VERSION 3.17)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

project(rtype CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

set(ClientSrc
Client/main.cpp
Client/GameClient.cpp)

set(EcsSrc
Ecs/Entity/Entity.cpp
Ecs/Entity/EntityManager.cpp
Ecs/Component/ComponentManager.cpp
Ecs/Component/sources/Acceleration.cpp
Ecs/Component/sources/Controlable.cpp
Ecs/Component/sources/Damage.cpp
Ecs/Component/sources/Health.cpp
Ecs/Component/sources/Hitbox.cpp
Ecs/Component/sources/Id.cpp
Ecs/Component/sources/Position.cpp
Ecs/Component/sources/Rotate.cpp
Ecs/Component/sources/Size.cpp
Ecs/Component/sources/Speed.cpp
Ecs/Component/sources/Sprite.cpp
Ecs/Component/sources/Text.cpp
Ecs/System/CollisionSystem.cpp
Ecs/System/MoveSystem.cpp
Ecs/System/GraphicSystem.cpp
Ecs/System/TextSystem.cpp
Ecs/System/ShootSystem.cpp
Ecs/System/SystemManager.cpp
Ecs/System/System.cpp
Ecs/Manager.cpp)

set(GraphicSrc
Graphics/Events.cpp
Graphics/InitSfml.cpp)

set(ServerSrc
server/main.cpp)

add_executable(r-type_client ${ClientSrc} ${GraphicSrc} ${EcsSrc})
add_executable(r-type_server ${ServerSrc} ${GraphicSrc} ${EcsSrc})