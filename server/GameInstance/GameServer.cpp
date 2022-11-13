/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameServer
*/

#include "GameServer.hpp"


GameServer::GameServer(int players, int roomId)
    :
    _roomAskingList(std::make_pair(players, 0)),
    _roomId(roomId),
    _inGame(false),
    _endGame(false)
{
}

void GameServer::initGameServer()
{
    sf::Packet prepSending;
    sf::Thread retrieve(&GameServer::retrievingPackets, this);

    _gameClock = std::make_shared<Clock>();
    _networkClock = std::make_shared<Clock>();
    _manager = std::make_shared<Manager>();
    _networkClock->addClockComponent(1, ECS::ComponentType::NETWORK, 10);
    _networkClock->addClockComponent(0, ECS::ComponentType::NETWORK, 50);
    _network.createConnection(_roomId);
    retrieve.launch();
    for (int i = 0; i < _roomAskingList.first; ++i)
        _playersReady.push_back(false);
    setManager();
    buildAllPlayers();
    buildAllEnnemies(15); //Temporary
    waitForFilledRoom();
    waitForClientsToBeReady();
    prepSending << Network::Networking::LAUNCHING;
    for (size_t id : _playerIds) {
        _sendingPackets.push_back(std::make_pair(_players[id], prepSending));
        std::cout << "Sending to :" << std::endl;
        std::cout << "ip=" << _players[id].first << std::endl;
        std::cout << "Port=" << _players[id].second << std::endl;
    }
    _inGame = true;
    gameLoop();
    retrieve.terminate();
    _endGame = true;
    while (_endGame);

}

std::pair<sf::IpAddress, unsigned int> GameServer::getUdpAddress() const
{
    return _UdpAddress;
}

std::pair<int, int> GameServer::getRoomAskingList() const
{
    return _roomAskingList;
}

/**
 * It creates a player entity and adds all the components needed for it to be a player
 *
 * @param playerNb The number of the player.
 *
 * @return The player entity
 */
ECS::Entity GameServer::GameServer::buildPlayer(int playerNb)
{
    ECS::Entity player = _manager->createEntity(ECS::EntityType::PLAYER);

    _manager->addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 100 + (200 * playerNb)));
    _manager->addComponent(player, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(0.0f, 0.0f));
    _manager->addComponent(player, ECS::ComponentType::CONTROLABLE, std::make_shared<ECS::Controlable>(true));
    _manager->addComponent(player, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(10));
    _manager->addComponent(player, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(100));
    _manager->addComponent(player, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(10, 30));
    _manager->addComponent(player, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(20));
    std::shared_ptr<ECS::Health> health = std::dynamic_pointer_cast<ECS::Health>(_manager->getComponent(player, ECS::ComponentType::HEALTH));
    std::cout << "Player Health : " << health->getHealth() << std::endl;
    _gameClock->addClockComponent(player.getId(), ECS::ComponentType::POSITION, 50);
    return player;
}

/**
 * It creates all the players in the game
 */
void GameServer::GameServer::buildAllPlayers()
{
    for (int i = 0; i < _roomAskingList.first; ++i) {
        _entities.push_back(buildPlayer(i));
        std::cout << i + 1 << " on " << _roomAskingList.first << " players created" << std::endl;
    }
}

/**
 * It creates an entity, adds all the components it needs, and returns it
 *
 * @return The entity created
 */
ECS::Entity GameServer::GameServer::buildEnnemy()
{
    ECS::Entity enemy = _manager->createEntity(ECS::EntityType::ENEMY);

    _manager->addComponent(enemy, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(0.0f, 0.0f));
    _manager->addComponent(enemy, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(10));
    _manager->addComponent(enemy, ECS::ComponentType::CONTROLABLE, std::make_shared<ECS::Controlable>(false));
    _manager->addComponent(enemy, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(10));
    _manager->addComponent(enemy, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(100));
    _manager->addComponent(enemy, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(11 * 3, 31 * 3));
    _manager->addComponent(enemy, ECS::ComponentType::PATTERN, std::make_shared<ECS::Pattern>(1920, 1080, 31 * 3, 11 * 3, ECS::PatternType::ZIGZAG));
    std::shared_ptr<ECS::Pattern> patt = std::dynamic_pointer_cast<ECS::Pattern>(_manager->getComponent(enemy, ECS::ComponentType::PATTERN));
    std::pair<int, int> pos = patt->getFirstPosition();
    _manager->addComponent(enemy, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(pos.first, pos.second));
    _gameClock->addClockComponent(enemy.getId(), ECS::ComponentType::PATTERN, 50);
    _gameClock->addClockComponent(enemy.getId(), ECS::ComponentType::POSITION, 50);
    return enemy;
}

/**
 * It builds all the ennemies for the current level
 *
 * @param maxEnn the number of enemies to create
 */
void GameServer::GameServer::buildAllEnnemies(int maxEnn)
{
    //here Build ennemies by level
    for (int i = 0; i < maxEnn; ++i) {
        _entities.push_back(buildEnnemy());
        std::cout << i + 1 << " on " << maxEnn << " enemies created" << std::endl;
    }
}

/**
 * It adds all the systems to the manager
 */
void GameServer::GameServer::setManager()
{
    auto &move = _manager->addSystem<ECS::MoveSystem>();
    move.setClock(_gameClock);
    auto &events = _manager->addSystem<ECS::EventsSystem>();
    events.setClock(_gameClock);
    auto &pattern = _manager->addSystem<ECS::PatternSystem>();
    pattern.setClock(_gameClock);
    _manager->addSystem<ECS::CollisionSystem>();
}

/**
 * It adds a player to the game server
 *
 * @param player The player's IP address and port.
 */
int GameServer::addPlayer(std::pair<sf::IpAddress, unsigned int> player) {
    int id = 0;

    _retrievedPackets.insert(std::make_pair(player, std::deque<std::pair<Network::Networking, sf::Packet>>()));
    if (!_playerIds.empty()) {
        for (id = 0; id < _roomAskingList.first; ++id) {
            if (std::find(_playerIds.begin(), _playerIds.end(), id) == _playerIds.end())
                break;
        }
    }
    _playerIds.push_back(id);
    _players.insert(std::make_pair(id, player));
    ++_roomAskingList.second;
    return id;
}


bool GameServer::getEndGame()
{
    return _endGame;
}

bool GameServer::playerDisconnect(int playerId)
{
    ECS::Entity ent;

    if (std::find(_playerIds.begin(), _playerIds.end(), playerId) == _playerIds.end())
        return false;
    if (_inGame) {
        for (size_t i = 0; i < _entities.size(); ++i) {
            if (static_cast<int>(_entities[i].getId()) == playerId) {
                ent = _entities[i];
                break;
            }
        }
        _entities.erase(std::find(_entities.begin(), _entities.end(), ent));
        --_roomAskingList.first;
    }
    --_roomAskingList.second;
    _retrievedPackets.erase(_players[playerId]);
    _players.erase(playerId);
    _playerIds.erase(std::find(_playerIds.begin(), _playerIds.end(), playerId));
    return !_inGame;
}

/**
 * It retrieves packets from the network and puts them in a queue
 */
void GameServer::retrievingPackets()
{
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> packet;

    while (1) {
        packet = _network.retrievePacket();
        if (packet.second.first != -1 || packet.second.second.getDataSize())
            _retrievedPackets[packet.first].push_back(packet.second);
        if (!_sendingPackets.empty() && _networkClock->componentUpdateNumber(1, ECS::ComponentType::NETWORK)) {
            _network.sendPacket(_sendingPackets[0]);
            _sendingPackets.pop_front();
        }
    }
}

/**
 * Wait until the room is filled.
 */
void GameServer::waitForFilledRoom()
{
    while (_roomAskingList.second != _roomAskingList.first);
}

void GameServer::playerIsReady(int playerId)
{
    _playersReady[playerId] = true;
}

void GameServer::playerIsNotReadyAnymore(int playerId)
{
    _playersReady[playerId] = false;
}

/**
 * It waits for all the clients to be ready
 */
void GameServer::waitForClientsToBeReady()
{
    while (std::find(_playersReady.begin(), _playersReady.end(), false) != _playersReady.end());
    std::cout << "OUT OF READY" << std::endl;
}

/**
 * It updates all the systems in the order they need to be updated
 */
void GameServer::GameServer::updateAll()
{
        _manager->getSystem<ECS::EventsSystem>().update();
        _manager->getSystem<ECS::PatternSystem>().update();
        _manager->getSystem<ECS::MoveSystem>().update();
        _manager->getSystem<ECS::CollisionSystem>().update();
        _manager->getSystem<ECS::EventsSystem>().clearEvents();
}

/**
 * It updates the game, and sends the new positions of all the entities to all the players
 */
void GameServer::GameServer::gameUpdate()
{
    sf::Packet prepSending;
    std::deque<std::pair<ECS::Entity, ECS::Position>> list;

    updateAll();
    if (_networkClock->componentUpdateNumber(0, ECS::ComponentType::NETWORK)) {
        for (size_t i = 0; i < _entities.size(); ++i)
            list.push_back(std::make_pair(_entities[i], *std::dynamic_pointer_cast<ECS::Position>(_manager->getComponent(_entities[i], ECS::ComponentType::POSITION))));
        prepSending << Network::Networking::GAMEUPDATE << list;
        for (size_t id : _playerIds) {
            _sendingPackets.push_back(std::make_pair(_players[id], prepSending));
        }
    }
}

/**
 * It checks if an entity has 0 health, if it's an enemy it respawns it, if it's a player it sends a
 * packet to all the players to tell them that the player died and then it deletes the player from the
 * game
 */
void GameServer::GameServer::checkForEntityDeath()
{
    sf::Packet prepSending;
    std::shared_ptr<ECS::Pattern> pattern;
    std::shared_ptr<ECS::Position> position;
    std::pair<int, int> pos;

    for (size_t i = 0; i < _entities.size(); ++i) {
        if (std::dynamic_pointer_cast<ECS::Health>(_manager->getComponent(_entities[i], ECS::ComponentType::HEALTH))->getHealth() == 0) {
            if (_entities[i].getType() == ECS::EntityType::ENEMY) {
                std::dynamic_pointer_cast<ECS::Health>(_manager->getComponent(_entities[i], ECS::ComponentType::HEALTH))->setHealth(std::dynamic_pointer_cast<ECS::Health>(_manager->getComponent(_entities[i], ECS::ComponentType::HEALTH))->getMaxHealth());
                pattern = std::dynamic_pointer_cast<ECS::Pattern>(_manager->getComponent(_entities[i], ECS::ComponentType::PATTERN));
                position = std::dynamic_pointer_cast<ECS::Position>(_manager->getComponent(_entities[i], ECS::ComponentType::POSITION));
                pos = pattern->getFirstPosition();
                position->setPosition_x(pos.first);
                position->setPosition_y(pos.second);
            } else {
                position = std::dynamic_pointer_cast<ECS::Position>(_manager->getComponent(_entities[i], ECS::ComponentType::POSITION));
                std::cout << "Position of player" << _entities[i].getId() << " : x=" << position->getPosition_x() << " y=" << position->getPosition_y() << std::endl;
                prepSending << Network::Networking::PLAYERDEATH << static_cast<int>(_entities[i].getId());
                for (size_t g = 0; g < _playerIds.size(); ++g)
                    _sendingPackets.push_back(std::make_pair(_players[_playerIds[g]], prepSending));
                _manager->destroyEntity(_entities[i]);
                _players.erase(_entities[i].getId());
                _playerIds.erase(std::find(_playerIds.begin(), _playerIds.end(), _entities[i].getId()));
                _entities.erase(_entities.begin() + i);
                --i;
                prepSending.clear();
            }
        }
    }
}

/**
 * It retrieves the buttons pressed by the player and sends them to the EventsSystem
 */
void GameServer::GameServer::getPlayersMove()
{
    std::shared_ptr<ECS::Position> playerPos;
    std::shared_ptr<ECS::Speed> playerSpeed;
    std::deque<Button> pressed;
    std::deque<int> nb;

    for (auto id : _playerIds) {
        if (_retrievedPackets[_players[id]].empty() || _retrievedPackets[_players[id]][0].first == Network::Networking::PLAYERUPDATE)
            continue;
        _retrievedPackets[_players[id]][0].second >> pressed;
        _retrievedPackets[_players[id]].erase(_retrievedPackets[_players[id]].begin());
        std::cout << "All buttons : " << std::endl;
        for (size_t i = 0; i < pressed.size(); ++i)
            std::cout << static_cast<int>(pressed[i]) << " ";
        std::cout << std::endl;
        _manager->getSystem<ECS::EventsSystem>().setEvents(id, pressed);
    }
}

/**
 * The game loop is the main loop of the game. It is responsible for getting the player's move,
 * updating the game, and checking for entity death
 */
void GameServer::GameServer::gameLoop()
{
    sf::Packet prepSending;

    std::cout << "In game loop" << std::endl;
    while (!_playerIds.empty()) {
        getPlayersMove();
        gameUpdate();
        checkForEntityDeath();
    }
}