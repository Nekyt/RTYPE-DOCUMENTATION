#include "Server.hpp"
#include <memory>
#include <SFML/System.hpp>
#include "../Ecs/Manager.hpp"
#include "../Ecs/System/CollisionSystem.hpp"
#include "../Ecs/System/GraphicSystem.hpp"
#include "../Ecs/System/MoveSystem.hpp"
#include "../Ecs/System/TextSystem.hpp"
#include "../Ecs/System/"

Server::Server::Server() : _up(true)
{
    _network.createConnection();
}

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

void Server::Server::setManager(std::shared_ptr<Manager> manager, int roomId)
{
    ECS::Entity player = manager->createEntity(ECS::EntityType::PLAYER);
    manager->addSystem<ECS::MoveSystem>();
    manager->addSystem<ECS::CollisionSystem>();
    manager->addSystem<ECS::TextSystem>();
    manager->addSystem<ECS::GraphicSystem>();

    if (_players[roomId] == 1)
        manager->addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 100));
    else if (_players[roomId] == 2) {
        manager->addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 300));
    } else if (_players[roomId] == 3) {
        manager->addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 500));
    } else if (_players[roomId] == 4) {
        manager->addComponent(player, ECS::ComponentType::POSITION, std::make_shared<ECS::Position>(100, 700));
    }
    std::shared_ptr<ECS::Position> position = std::dynamic_pointer_cast<ECS::Position>(manager->getComponent(player, ECS::ComponentType::POSITION));
    manager->addComponent(player, ECS::ComponentType::SPRITE, std::make_shared<ECS::Sprite>(*_graphical->getTexture("player"), 2, 2, 0, 0, 0, 0, sf::Vector2f(position->getPosition_x(), position->getPosition_y())));
    manager->addComponent(player, ECS::ComponentType::ACCELERATION, std::make_shared<ECS::Acceleration>(0, 0));
    manager->addComponent(player, ECS::ComponentType::CONTROLABLE, std::make_shared<ECS::Controlable>(true));
    manager->addComponent(player, ECS::ComponentType::DAMAGE, std::make_shared<ECS::Damage>(10));
    manager->addComponent(player, ECS::ComponentType::HEALTH, std::make_shared<ECS::Health>(100));
    manager->addComponent(player, ECS::ComponentType::HITBOX, std::make_shared<ECS::Hitbox>(10, 30));
    manager->addComponent(player, ECS::ComponentType::SPEED, std::make_shared<ECS::Speed>(12));
    _mapPlayers[nbrPlayer] = player;

}

void Server::Server::updateAll(std::shared_ptr<Manager> manager)
{
    manager->getSystem<ECS::EventsSystem>().update();
    manager->getSystem<ECS::CollisionSystem>().update();
    manager->getSystem<ECS::MoveSystem>().update();
}

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


void Server::Server::waitForClientsToBeReady(int roomId)
{
    int g = _players[roomId];

    for (int i = 0; i < _clients[roomId].size(); ++i)
        _network.sendEnum(_clients[roomId][i], Network::Networking::READY);
    while (g != 0) {
        for (int i = 0; i < _inGamePackets[roomId].size(); ++i) {
            if (!_inGamePackets[roomId][i].empty()) {
                --g;
                _inGamePackets[roomId][i].clear();
            }
        }
    }
}

void Server::Server::gameLoop()
{
    int roomId(_idArg);
    _idArg = -1;
    //std::shared_ptr<Manager> manager = std::make_shared<Manager>();

    //setManager(manager, roomId);
    waitForFilledRoom(roomId);
    waitForClientsToBeReady(roomId);
    //gameUpdate(roomId, manager);

}