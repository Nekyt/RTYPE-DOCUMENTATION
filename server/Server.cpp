#include "Server.hpp"
#include <unistd.h>

Server::Server::Server() : _up(true), _idArg(-1)
{
    _clock = std::make_shared<Clock>();
    _network.createConnection();
}


/**
 * It loops through the packets that have been retrieved from the network and puts them in a vector
 */
void Server::Server::loopPackets()
{
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> packet;

    while (1) {
        packet = _network.retrievePacket();
        if (packet.second.first != -1 || packet.second.second.getDataSize())
            _retrievedPackets.push_back(packet);
        if (!_sendingPackets.empty()) {
            _network.sendPacket(_sendingPackets[0]);
            _sendingPackets.erase(_sendingPackets.begin());
        }
    }
}

/**
 * It's a loop that will check if there's any packet to retrieve, and if there is, it will check what
 * kind of packet it is, and will do the appropriate action
 */
void Server::Server::serverLoop()
{
    sf::Thread thread(&Server::Server::gameLoop, this);
    sf::Thread retrieve(&Server::Server::loopPackets, this);
    sf::Packet prepSending;
    sf::Packet back;
    int secondNb = 0;
    int i = 0;
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> packet;

    retrieve.launch();
    while (_up) {
        if (!_retrievedPackets.empty()) {
            packet = _retrievedPackets[0];
            _retrievedPackets.erase(_retrievedPackets.begin());
            std::cout << "LOG : Network Enum received : " << packet.second.first << std::endl;
            if (packet.second.first == Network::Networking::ROOMASKING) {
                prepSending << Network::Networking::ROOMASKING << _roomsID;
                _sendingPackets.push_back(std::make_pair(packet.first, prepSending));
            } else if (packet.second.first == Network::Networking::ROOMCREATION) {
                packet.second.second >> secondNb;
                if (_roomsID.empty())
                    _roomsID.push_back(0);
                else
                    _roomsID.push_back(_roomsID[_roomsID.size() - 1] + 1);
                _clock->addClockComponent(_roomsID[_roomsID.size() - 1], ECS::ComponentType::NETWORK, 50);
                _inGamePackets.insert(std::make_pair(_roomsID[_roomsID.size() - 1], std::vector<std::vector<sf::Packet>>()));
                _players.insert(std::make_pair(_roomsID.size() - 1, secondNb));
                _idArg = _roomsID[_roomsID.size() - 1];
                std::cout << "LOG : Creating new room" << std::endl;
                thread.launch();
            } else if (packet.second.first == Network::Networking::ROOMCONNECT) {
                packet.second.second >> secondNb;
                if (static_cast<int>(_inGamePackets[secondNb].size()) - 1 == _players[secondNb]) {
                    prepSending << Network::Networking::ERROR << "This room already have enough players.";
                    _sendingPackets.push_back(std::make_pair(packet.first, prepSending));
                } else {
                    _inGamePackets[secondNb].push_back(std::vector<sf::Packet>{packet.second.second});
                    _clients[secondNb].push_back(packet.first);
                }
            } else {
                for (i = 0; i < static_cast<int>(_clients[secondNb].size()) && _clients[secondNb][i] != packet.first; ++i);
                packet.second.second >> secondNb;
                if (packet.second.first == 4) {
                    back << packet.second.first << packet.second.second;
                    _inGamePackets[secondNb][i].push_back(back);
                } else {
                    _inGamePackets[secondNb][i].push_back(packet.second.second);
                }
            }
            prepSending.clear();
        }
    }
    retrieve.terminate();
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
    manager->addComponent(player, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(20));
    std::shared_ptr<ECS::Health> health = std::dynamic_pointer_cast<ECS::Health>(manager->getComponent(player, ECS::ComponentType::HEALTH));
    std::cout << "Player Health : " << health->getHealth() << std::endl;
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

    for (int i = 0; i < _players[roomId]; ++i) {
        entities.push_back(buildPlayer(i, manager));
        std::cout << i + 1 << " on " << _players[roomId] << " players created" << std::endl;
    }
    return entities;
}

/**
 * It builds an enemy
 *
 * @param manager the manager of the game
 *
 * @return The entity created.
 */
ECS::Entity Server::Server::buildEnnemy(std::shared_ptr<Manager> manager, std::shared_ptr<Clock> clock)
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
    clock->addClockComponent(enemy.getId(), ECS::ComponentType::POSITION, 400);
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
std::vector<ECS::Entity> Server::Server::buildAllEnnemies(std::shared_ptr<Manager> manager, int maxEnn, std::shared_ptr<Clock> clock)
{
    std::vector<ECS::Entity> entities;

    for (int i = 0; i < maxEnn; ++i) {
        entities.push_back(buildEnnemy(manager, clock));
        std::cout << i + 1 << " on " << maxEnn << " enemies created" << std::endl;
    }
    return entities;
}

/**
 * It adds the systems that the game will use
 *
 * @param manager The manager that will be used to manage the entities.
 * @param roomId The id of the room that the manager is being set for.
 */
void Server::Server::setManager(std::shared_ptr<Manager> manager, std::shared_ptr<Clock> clock)
{
    auto &move = manager->addSystem<ECS::MoveSystem>();
    move.setClock(clock);
    auto &collision = manager->addSystem<ECS::CollisionSystem>();
    //manager->addSystem<ECS::TextSystem>();
    //manager->addSystem<ECS::GraphicSystem>();
}

/**
 * It updates all the systems in the manager
 *
 * @param manager The manager that the systems are in.
 */
void Server::Server::updateAll(std::shared_ptr<Manager> manager)
{
        std::cout << "BEGINNING SYSTEMS UPDATES" << std::endl;
        //manager->getSystem<ECS::EventsSystem>().update();
        //std::cout << "Done Events" << std::endl;
        manager->getSystem<ECS::CollisionSystem>().update();
        manager->getSystem<ECS::MoveSystem>().update();
        std::cout << "OUT OF SYSTEMS UPDATES" << std::endl;
}

/**
 * It waits for the room to be filled with players
 *
 * @param roomId The id of the room you want to wait for.
 */
void Server::Server::waitForFilledRoom(int roomId)
{
    sf::Packet prepSending;

    std::cout << "BEGIN WAIT FOR FILLED ROOM" << std::endl;
    while (static_cast<int>(_clients[roomId].size()) < _players[roomId]) {
        for (size_t i = 0; i < _inGamePackets[roomId].size(); ++i) {
            if (!_inGamePackets[roomId][i].empty()) {
                _inGamePackets[roomId][i].clear();
                prepSending << Network::Networking::CONNECTED << static_cast<int>(i);
                _sendingPackets.push_back(std::make_pair(_clients[roomId][i], prepSending));
                prepSending.clear();
            }
        }
    }
    for (size_t i = 0; i < _inGamePackets[roomId].size(); ++i) {
        if (!_inGamePackets[roomId][i].empty()) {
            _inGamePackets[roomId][i].clear();
            prepSending << Network::Networking::CONNECTED << static_cast<int>(i);
            _sendingPackets.push_back(std::make_pair(_clients[roomId][i], prepSending));
            prepSending.clear();
        }
    }
    std::cout << "END WAIT FOR FILLED ROOM" << std::endl;
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
    sf::Packet pack;
    int net;

    pack << Network::Networking::READY;
    for (size_t i = 0; i < _clients[roomId].size(); ++i) {
        std::cout << "SENDING READY" << std::endl;
        _sendingPackets.push_back(std::make_pair(_clients[roomId][i], pack));
    }
    while (g != 0) {
        for (size_t i = 0; i < _inGamePackets[roomId].size(); ++i) {
            if (!_inGamePackets[roomId][i].empty()) {
                pack = _inGamePackets[roomId][i][0];
                pack >> net;
                if (net == Network::Networking::READY)
                    --g;
                _inGamePackets[roomId][i].erase(_inGamePackets[roomId][i].begin());
                pack.clear();
            }
        }
    }
}

/**
 * It updates all the entities, then it puts them in a vector of pairs, then it puts the vector in a
 * packet, then it puts the packet in a vector of pairs with the client as the first element
 *
 * @param roomId The id of the room to send the packet to.
 * @param manager The manager of the game
 * @param entities a vector of entities that are in the room
 */
void Server::Server::gameUpdate(int roomId, std::shared_ptr<Manager> manager, std::vector<ECS::Entity> entities)
{
    sf::Packet prepSending;
    std::vector<std::pair<ECS::Entity, ECS::Position>> list;

    //std::cout << "In game update" << std::endl;
    //manager->getSystem<ECS::EventsSystem>();
    //std::cout << "Out of game update" << std::endl;
    updateAll(manager);
    if (_clock->componentUpdateNumber(roomId, ECS::ComponentType::NETWORK)) {
        for (size_t i = 0; i < entities.size(); ++i)
            list.push_back(std::make_pair(entities[i], *std::dynamic_pointer_cast<ECS::Position>(manager->getComponent(entities[i], ECS::ComponentType::POSITION))));
        prepSending << Network::Networking::GAMEUPDATE << list;
        for (size_t i = 0; i < _clients[roomId].size(); ++i) {
            _sendingPackets.push_back(std::make_pair(_clients[roomId][i], prepSending));
        }
    }
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
    sf::Packet prepSending;
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
                position = std::dynamic_pointer_cast<ECS::Position>(manager->getComponent(entities[i], ECS::ComponentType::POSITION));
                std::cout << "Position of player" << i << " : x=" << position->getPosition_x() << " y=" << position->getPosition_y() << std::endl;
                /*prepSending << Network::Networking::PLAYERDEATH << static_cast<int>(entities[i].getId());
                for (size_t g = 0; g < _clients[roomId].size(); ++g)
                    _sendingPackets.push_back(std::make_pair(_clients[roomId][g], prepSending));*/
                //entities.erase(entities.begin() + i);
                //_clients[roomId].erase(_clients[roomId].begin() + i);
                //_inGamePackets[roomId].erase(_inGamePackets[roomId].begin() + i);
                std::dynamic_pointer_cast<ECS::Health>(manager->getComponent(entities[i], ECS::ComponentType::HEALTH))->setHealth(std::dynamic_pointer_cast<ECS::Health>(manager->getComponent(entities[i], ECS::ComponentType::HEALTH))->getMaxHealth());
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
    std::vector<int> nb;

    std::cout << "CHECKING BUTTONS" << std::endl;
    for (size_t i = 0; i < _clients[roomId].size(); ++i) {
        if (_inGamePackets[roomId][i].empty())
            continue;
        _inGamePackets[roomId][i][0] >> pressed;
        /*for (auto a : nb) {
            std::cout << a << " ";
            pressed.push_back(static_cast<Button>(a));
        }
        std::cout<< std::endl;*/
        _inGamePackets[roomId][i].erase(_inGamePackets[roomId][i].begin());
        std::cout << "All buttons : " << std::endl;
        for (size_t i = 0; i < pressed.size(); ++i)
            std::cout << static_cast<int>(pressed[i]) << " ";
        std::cout << std::endl;
        playerPos = std::dynamic_pointer_cast<ECS::Position>(manager->getComponent(entities[i], ECS::ComponentType::POSITION));
        playerSpeed = std::dynamic_pointer_cast<ECS::Speed>(manager->getComponent(entities[i], ECS::ComponentType::SPEED));
        while (!pressed.empty()) {
            playerSpeed->setSpeed(playerSpeed->getMaxSpeed());
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
    std::cout << "OUT OF CHECKING BUTTONS" << std::endl;
}

/**
 * It's the main loop of the game, it's where the game is actually played
 */
void Server::Server::gameLoop()
{
    sf::Packet prepSending;
    int roomId(_idArg);
    std::shared_ptr<Manager> manager = std::make_shared<Manager>();
    std::vector<ECS::Entity> entities;
    std::shared_ptr<Clock> clock = std::make_shared<Clock>();

    _idArg = -1;
    setManager(manager, clock);
    entities = buildAllPlayers(manager, roomId);
    entities = entities + (buildAllEnnemies(manager, MAX_ENEMIES, clock));
    waitForFilledRoom(roomId);
    waitForClientsToBeReady(roomId);
    prepSending << Network::Networking::LAUNCHING;
    for (size_t i = 0; i < _clients[roomId].size(); ++i)
        _sendingPackets.push_back(std::make_pair(_clients[roomId][i], prepSending));
    while (!_clients[roomId].empty()) {
        gameUpdate(roomId, manager, entities);
        getPlayersMove(roomId, entities, manager);
        checkForEntityDeath(roomId, manager, entities);
    }
    _clock->eraseClockComponent(roomId, ECS::ComponentType::NETWORK);
    std::cout << std::endl << "ROOM " << roomId << " IS CLOSING, GAME OVER" << std::endl << std::endl;
}