#include "Server.hpp"

Server::Server::Server() : _up(true)
{
    _network.createConnection();
}

void Server::Server::serverLoop()
{
    int free = 0;
    int secondNb = 0;
    int i = 0;
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> packet;

    while (_up) {
        packet = _network.retrievePacket();
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
        /***********************************************************************//*
                                      gameLoop
        *//***********************************************************************/
        } else if (packet.second.first == Network::Networking::ROOMCONNECT) {
            packet.second.second >> secondNb;
            if (_inGamePackets[secondNb].size() - 1 == _players[secondNb]) {
                _network.sendError(packet.first, "This room already have enough players.");
            } else {
                _inGamePackets[secondNb].push_back(std::vector<sf::Packet>{packet.second.second});
            }
        } else if (packet.second.first == Network::Networking::PLAYERUPDATE) {
            packet.second.second >> secondNb;
            for (i = 0; i < _clients[secondNb].size() && _clients[secondNb][i] != packet.first; ++i);
            _inGamePackets[secondNb][i].push_back(packet.second.second);
        }
    }
}

/*void Server::Server::setManager(std::shared_ptr<Manager> manager, int roomId)
{
    manager->addSystem<ECS::MoveSystem>();
    manager->addSystem<ECS::CollisionSystem>();
    manager->addSystem<ECS::TextSystem>();
    manager->addSystem<ECS::GraphicSystem>();

}
*/
void Server::Server::waitForFilledRoom(int roomId)
{
    while (_clients[roomId].size() - 1 > _players[roomId]) {
        for (int i = 0; i < _inGamePackets[roomId].size(); ++i) {
            if (!_inGamePackets[roomId][i].empty()) {
                _inGamePackets[roomId][i].clear();
                _network.sendPlayerId(_clients[roomId][i], i);
            }
        }
    }
    /*for (int i = 0; i < _inGamePackets[roomId].size(); ++i) {
        if (!_inGamePackets[roomId][i].empty()) {
            _inGamePackets[roomId][i].clear();
            _network.sendPlayerId(_clients[roomId][i], i);
        }
    }*/
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

void Server::Server::gameLoop(int roomId)
{
    //std::shared_ptr<Manager> manager = std::make_shared<Manager>();

    //setManager(manager, roomId);
    waitForFilledRoom(roomId);
    waitForClientsToBeReady(roomId);
    //gameUpdate(roomId, manager);

}