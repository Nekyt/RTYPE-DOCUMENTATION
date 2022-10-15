/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameServer
*/

#include "GameServer.hpp"

GameServer::GameServer()
{
}


void GameServer::handleNewClient(int nbrPlayer)
{
    ECS::Entity player = _manager.createEntity(ECS::EntityType::PLAYER);

    if (nbrPlayer == 1)
        _manager.addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 100);
    else if (nbrPlayer == 2)
        _manager.addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 300);
    else if (nbrPlayer == 3)
        _manager.addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 500);
    else if (nbrPlayer == 4)
        _manager.addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 700);
    std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_manager.getComponent(player, ECS::ComponentType::POSITION));
    _manager.addComponent(player, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("player"), 2, 2, 0, 0, 0, 0, sf::Vector2f(position->getPosition_x(), position->getPosition_y())));
    _manager.addComponent(player, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(0, 0);
    _manager.addComponent(player, ECS::ComponentType::CONTROLABLE, std::make_shared<ECS::Controlable>(true);
    _manager.addComponent(player, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(10);
    _manager.addComponent(player, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(100);
    _manager.addComponent(player, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(10, 30);
    _mapPlayers[nbrPlayer] = player;
}

void GameServer::AddNewCommands(int nbrPlayer, Button button)
{
    ECS::Entity entityPlayer = _mapPlayers[nbrPlayer];
    _manager.getSystem<ECS::EventsSystem>().setEvents(entityPlayer, button);
}

void GameServer::updateAll()
{
    try
    {
        _manager.getSystem<ECS::EventsSystem>().update();
        _manager.getSystem<ECS::CollisionSystem>().update();
        _manager.getSystem<ECS::MoveSystem>().update();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}