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

/**
 * It creates a player entity and adds all the components needed to make it work
 * 
 * @param nbrPlayer the number of the player
 */
void GameServer::handleNewClient(int nbrPlayer)
{
    ECS::Entity player = _manager.createEntity(ECS::EntityType::PLAYER);

    if (nbrPlayer == 1)
        _manager.addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 100));
    else if (nbrPlayer == 2)
        _manager.addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 300));
    else if (nbrPlayer == 3)
        _manager.addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 500));
    else if (nbrPlayer == 4)
        _manager.addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 700));
    std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_manager.getComponent(player, ECS::ComponentType::POSITION));
    _manager.addComponent(player, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("player"), 2, 2, 0, 0, 0, 0, sf::Vector2f(position->getPosition_x(), position->getPosition_y())));
    _manager.addComponent(player, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(0, 0));
    _manager.addComponent(player, ECS::ComponentType::CONTROLABLE, std::make_shared<ECS::Controlable>(true));
    _manager.addComponent(player, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(10));
    _manager.addComponent(player, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(100));
    _manager.addComponent(player, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(10, 30));
    _manager.addComponent(player, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(12));
    _mapPlayers[nbrPlayer] = player;
}

/**
 * It creates an enemy entity and adds all the components it needs
 * 
 * @param nbrEnemy the number of the enemy
 */
void GameServer::handleNewEnemy(int nbrEnemy)
{
    ECS::Entity enemy = _manager.createEntity(ECS::EntityType::ENEMY);

    _manager.addComponent(enemy, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 100));
    std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(_manager.getComponent(enemy, ECS::ComponentType::POSITION));
    _manager.addComponent(enemy, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("enemy"), 2, 2, 0, 0, 0, 0, sf::Vector2f(position->getPosition_x(), position->getPosition_y())));
    _manager.addComponent(enemy, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(0, 0));
    _manager.addComponent(enemy, ECS::ComponentType::CONTROLABLE, std::make_shared<ECS::Controlable>(false));
    _manager.addComponent(enemy, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(10));
    _manager.addComponent(enemy, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(100));
    _manager.addComponent(enemy, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(10, 30));
    _manager.addComponent(enemy, ECS::ComponentType::PATTERN, std::make_shared<ECS::Pattern>(15, 15, 10, 10));
    _mapEnemys[nbrEnemy] = enemy;
}

/**
 * It adds a new command to the player's entity
 * 
 * @param nbrPlayer The player number
 * @param button The button that was pressed
 */
void GameServer::AddNewCommands(int nbrPlayer, Button button)
{
    ECS::Entity entityPlayer = _mapPlayers[nbrPlayer];
    _manager.getSystem<ECS::EventsSystem>().setEvents(entityPlayer, button);
}

/**
 * It creates a new player for each player slot
 * 
 * @param maxPlayers The maximum number of players that can be connected to the
 * server.
 */
void GameServer::createAllPlayer(int maxPlayers)
{
    for (int i = 0; i < maxPlayers; i++)
        handleNewClient(i);
}

/**
 * It creates all the enemies
 * 
 * @param maxEnemy The maximum number of enemies that can be created.
 */
void GameServer::createAllEnemy(int maxEnemy)
{
    for (int i = 0; i < maxEnemy; i++)
        handleNewEnemy(i);
}

/**
 * It returns a map of all the players in the game
 * 
 * @return A map of int and ECS::Entity
 */
std::map<int, ECS::Entity> GameServer::getPlayerList() const
{
    return _mapPlayers;
}

/**
 * It returns the map of enemys.
 * 
 * @return A map of int and ECS::Entity
 */
std::map<int, ECS::Entity> GameServer::getEnemyList() const
{
    return _mapEnemys;
}

/**
 * It updates all the systems
 */
void GameServer::updateAll()
{
    try {
        _manager.getSystem<ECS::EventsSystem>().update();
        _manager.getSystem<ECS::CollisionSystem>().update();
        _manager.getSystem<ECS::MoveSystem>().update();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}