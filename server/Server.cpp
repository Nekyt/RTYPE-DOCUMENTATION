#include "Server.hpp"

Server::Server::Server() : _up(true), _idArg(-1)
{
    _network.createConnection();
}

/**
 * It's a loop that waits for packets and then does stuff with them
 */
void Server::Server::serverLoop()
{
    sf::Thread thread(&Server::Server::gameLoop, this);
    int free = 0;
    int secondNb = 0;
    int i = 0;

    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> packet;

    while (_up) {
        packet = _network.retrievePacket();
        std::cout << packet.second.first << std::endl;
        if (packet.second.first == Network::Networking::ROOMASKING)
            _network.sendRoomList(packet.first, _roomsID);
        else if (packet.second.first == Network::Networking::ROOMCREATION) {
            packet.second.second >> secondNb;
            if (_roomsID.empty() || _roomsID[0] > 0)
                _roomsID.push_back(0);
            else
                _roomsID.push_back(_roomsID[_roomsID.size() - 1] + 1);
            _inGamePackets.insert(std::make_pair(_roomsID[_roomsID.size() - 1], std::vector<std::vector<sf::Packet>>()));
            _players.insert(std::make_pair(_roomsID.size() - 1, secondNb));
            _idArg = _roomsID[_roomsID.size() - 1];
            std::cout << "LOG : Creating new room" << std::endl;
            thread.launch();
        } else if (packet.second.first == Network::Networking::ROOMCONNECT) {
            packet.second.second >> secondNb;
            if (_inGamePackets[secondNb].size() - 1 == _players[secondNb]) {
                _network.sendError(packet.first, "This room already have enough players.");
            } else {
                _inGamePackets[secondNb].push_back(std::vector<sf::Packet>{packet.second.second});
                _clients[secondNb].push_back(packet.first);
            }
        } else if (packet.second.first == Network::Networking::PLAYERUPDATE) {
            packet.second.second >> secondNb;
            for (i = 0; i < _clients[secondNb].size() && _clients[secondNb][i] != packet.first; ++i);
            _inGamePackets[secondNb][i].push_back(packet.second.second);
        }
    }
}

/**
 * It creates a player entity and adds all the components it needs
 *
 * @param playerNb The number of the player.
 * @param manager The manager that will be used to create the entity.
 *
 * @return The player entity.
 */
ECS::Entity Server::Server::buildPlayer(int playerNb, std::shared_ptr<Manager> manager)
{
    ECS::Entity player = manager->createEntity(ECS::EntityType::PLAYER);

    manager->addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 100 + (200 * playerNb)));
    manager->addComponent(player, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(0, 0));
    manager->addComponent(player, ECS::ComponentType::CONTROLABLE, std::make_shared<ECS::Controlable>(true));
    manager->addComponent(player, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(10));
    manager->addComponent(player, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(100));
    manager->addComponent(player, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(10, 30));
    manager->addComponent(player, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(12));
    return player;
}

/**
 * It builds all the players for a room
 *
 * @param manager The manager that will be used to create the entities.
 * @param roomId The id of the room the player is in.
 *
 * @return A vector of entities.
 */
std::vector<ECS::Entity> Server::Server::buildAllPlayers(std::shared_ptr<Manager> manager, int roomId)
{
    std::vector<ECS::Entity> entities;

    for (int i = 0; i < _players[roomId]; ++i)
        entities.push_back(buildPlayer(i, manager));
    return entities;
}

/**
 * It builds an enemy
 *
 * @param manager the manager of the game
 *
 * @return The entity created.
 */
ECS::Entity Server::Server::buildEnnemy(std::shared_ptr<Manager> manager)
{
    ECS::Entity enemy = manager->createEntity(ECS::EntityType::ENEMY);

    manager->addComponent(enemy, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(0, 0));
    manager->addComponent(enemy, ECS::ComponentType::CONTROLABLE, std::make_shared<ECS::Controlable>(false));
    manager->addComponent(enemy, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(10));
    manager->addComponent(enemy, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(100));
    manager->addComponent(enemy, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(10, 30));
    manager->addComponent(enemy, ECS::ComponentType::PATTERN, std::make_shared<ECS::Pattern>(1920, 1080, 10, 30, ECS::PatternType::ZIGZAG));
    std::shared_ptr<ECS::Pattern> patt = std::dynamic_pointer_cast<ECS::Pattern>(manager->getComponent(enemy, ECS::ComponentType::PATTERN));
    std::pair<int, int> pos = patt->getFirstPosition();
    manager->addComponent(enemy, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(pos.first, pos.second));
    return enemy;
}


/**
 * It builds a vector of ennemies
 *
 * @param manager the manager that will be used to create the entities
 * @param maxEnn the maximum number of ennemies to spawn
 *
 * @return A vector of entities
 */
std::vector<ECS::Entity> Server::Server::buildAllEnnemies(std::shared_ptr<Manager> manager, int maxEnn)
{
    std::vector<ECS::Entity> entities;
    for (int i = 0; i < maxEnn; ++i)
        entities.push_back(buildEnnemy(manager));
    return entities;
}

/**
 * It adds the systems that the game will use
 *
 * @param manager The manager that will be used to manage the entities.
 * @param roomId The id of the room that the manager is being set for.
 */
void Server::Server::setManager(std::shared_ptr<Manager> manager, int roomId)
{

    manager->addSystem<ECS::MoveSystem>();
    manager->addSystem<ECS::CollisionSystem>();
    manager->addSystem<ECS::TextSystem>();
    manager->addSystem<ECS::GraphicSystem>();
}

/**
 * It updates all the systems in the manager
 *
 * @param manager The manager that the systems are in.
 */
void Server::Server::updateAll(std::shared_ptr<Manager> manager)
{
    try {
        manager->getSystem<ECS::EventsSystem>().update();
        manager->getSystem<ECS::CollisionSystem>().update();
        manager->getSystem<ECS::MoveSystem>().update();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * It waits for the room to be filled with players
 *
 * @param roomId The id of the room you want to wait for.
 */
void Server::Server::waitForFilledRoom(int roomId)
{
    while (_clients[roomId].size() - 1 > _players[roomId]) {
        for (int i = 0; i < _inGamePackets[roomId].size(); ++i) {
            std::cout << i << std::endl;
            if (!_inGamePackets[roomId][i].empty()) {
                _inGamePackets[roomId][i].clear();
                std::cout << _inGamePackets[roomId][i].size() << std::endl;
                _network.sendPlayerId(_clients[roomId][i], i);
            }
        }
    }
    for (int i = 0; i < _inGamePackets[roomId].size(); ++i) {
        if (!_inGamePackets[roomId][i].empty()) {
            _inGamePackets[roomId][i].clear();
            _network.sendPlayerId(_clients[roomId][i], i);
        }
    }
}


/**
 * It sends a READY enum to all the clients in the room, then waits for all the clients to send a
 * packet back
 *
 * @param roomId The id of the room you want to wait for clients to be ready in.
 */
void Server::Server::waitForClientsToBeReady(int roomId)
{
    int g = _players[roomId];

    for (size_t i = 0; i < _clients[roomId].size(); ++i)
        _network.sendEnum(_clients[roomId][i], Network::Networking::READY);
    while (g != 0) {
        for (size_t i = 0; i < _inGamePackets[roomId].size(); ++i) {
            if (!_inGamePackets[roomId][i].empty()) {
                --g;
                _inGamePackets[roomId][i].clear();
            }
        }
    }
}

/**
 * It updates the game.
 *
 * @param roomId The id of the room that the game is in.
 * @param manager The manager that contains all the entities
 * @param entities A vector of all the entities in the room.
 */
void Server::Server::gameUpdate(int roomId, std::shared_ptr<Manager> manager, std::vector<ECS::Entity> entities)
{
    std::vector<std::pair<ECS::Entity, ECS::Position>> list;
    updateAll(manager);
    for (size_t i = 0; i < entities.size(); ++i)
        list.push_back(std::make_pair(entities[i], *std::dynamic_pointer_cast<ECS::Position>(manager->getComponent(entities[i], ECS::ComponentType::POSITION))));
    for (size_t i = 0; i < _clients[roomId].size(); ++i)
        _network.sendGameUpdate(_clients[roomId][i], list);
}

/**
 * It checks if an entity has died, and if it has, it either respawns it or removes it from the game
 *
 * @param roomId The id of the room in which the entities are.
 * @param manager The ECS manager
 * @param entities The entities in the room
 */
void Server::Server::checkForEntityDeath(int roomId, std::shared_ptr<Manager> manager, std::vector<ECS::Entity> entities)
{
    std::shared_ptr<ECS::Pattern> pattern;
    std::shared_ptr<ECS::Position> position;
    std::pair<int, int> pos;

    for (size_t i = 0; i < entities.size(); ++i) {
        if (std::dynamic_pointer_cast<ECS::Health>(manager->getComponent(entities[i], ECS::ComponentType::HEALTH))->getHealth() == 0) {
            if (entities[i].getType() == ECS::EntityType::ENEMY) {
                std::dynamic_pointer_cast<ECS::Health>(manager->getComponent(entities[i], ECS::ComponentType::HEALTH))->setHealth(std::dynamic_pointer_cast<ECS::Health>(manager->getComponent(entities[i], ECS::ComponentType::HEALTH))->getMaxHealth());
                pattern = std::dynamic_pointer_cast<ECS::Pattern>(manager->getComponent(entities[i], ECS::ComponentType::PATTERN));
                position = std::dynamic_pointer_cast<ECS::Position>(manager->getComponent(entities[i], ECS::ComponentType::POSITION));
                pos = pattern->getFirstPosition();
                position->setPosition_x(pos.first);
                position->setPosition_y(pos.second);
            } else {
                for (size_t g = 0; g < _clients[roomId].size(); ++g)
                    _network.sendPlayerDeathOrDisconnect(_clients[roomId][g], entities[i].getId(), Network::Networking::PLAYERDEATH);
                entities.erase(entities.begin() + i);
                _clients[roomId].erase(_clients[roomId].begin() + i);
                _inGamePackets[roomId].erase(_inGamePackets[roomId].begin() + i);
            }
        }
    }
}

/**
 * It gets the players' moves from the packets and applies them to the entities
 *
 * @param roomId The id of the room in which the players are playing.
 * @param entities a vector of entities that are in the game
 * @param manager The ECS manager
 */
void Server::Server::getPlayersMove(int roomId, std::vector<ECS::Entity> entities, std::shared_ptr<Manager> manager)
{
    std::shared_ptr<ECS::Position> playerPos;
    std::shared_ptr<ECS::Speed> playerSpeed;
    std::vector<Button> pressed;
    Button but;
    int free;

    for (size_t i = 0; i < _clients[roomId].size(); ++i) {
        _inGamePackets[roomId][i][0] >> free >> pressed;
        _inGamePackets[roomId][i].erase(_inGamePackets[roomId][i].begin());
        playerPos = std::dynamic_pointer_cast<ECS::Position>(manager->getComponent(entities[i], ECS::ComponentType::POSITION));
        playerSpeed = std::dynamic_pointer_cast<ECS::Speed>(manager->getComponent(entities[i], ECS::ComponentType::SPEED));
        while (!pressed.empty()) {
            but = pressed[0];
            pressed.erase(pressed.begin());
            if (but == Button::Up && but != Button::Down)
                playerPos->setPosition_y(playerPos->getPosition_y() - playerSpeed->getSpeed());
            if (but == Button::Down && but != Button::Up)
                playerPos->setPosition_y(playerPos->getPosition_y() + playerSpeed->getSpeed());
            if (but == Button::Right && but != Button::Left)
                playerPos->setPosition_x(playerPos->getPosition_x() + playerSpeed->getSpeed());
            if (but == Button::Left && but != Button::Right)
                playerPos->setPosition_x(playerPos->getPosition_x() - playerSpeed->getSpeed());
            //if (but == Button::Space)
        }
    }
}

/**
 * It creates a manager, builds all the players and enemies, waits for the room to be filled and for
 * the clients to be ready, and then starts the game loop
 */
void Server::Server::gameLoop()
{
    int roomId(_idArg);
    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    std::vector<ECS::Entity> entities;

    _idArg = -1;
    setManager(manager, roomId);
    entities = buildAllPlayers(manager, roomId);
    entities = entities + (buildAllEnnemies(manager, MAX_ENEMIES));
    waitForFilledRoom(roomId);
    waitForClientsToBeReady(roomId);
    for (size_t i = 0; i < _clients[roomId].size(); ++i)
        _network.sendEnum(_clients[roomId][i], Network::Networking::LAUNCHING);
    while (!_clients[roomId].empty()) {
        gameUpdate(roomId, manager, entities);
        checkForEntityDeath(roomId, manager, entities);
    }
    std::cout << std::endl << "ROOM " << roomId << " IS CLOSING, GAME OVER" << std::endl << std::endl;
}