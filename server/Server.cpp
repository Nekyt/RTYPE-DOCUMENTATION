#include "Server.hpp"
#include <unistd.h>

Server::Server::Server() : _up(true)
{
    _clock = std::make_shared<Clock>();
    _network.createConnection();
}

/**
 * It loops through the packets that have been retrieved from the network and puts them in a deque
 */
void Server::Server::loopPackets()
{
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> packet;

    while (1) {
        packet = _network.retrieveTcpPacket();
        if (packet.second.first != -1 || packet.second.second.getDataSize())
            _retrievedPackets.push_back(packet);
        if (!_sendingPackets.empty() && _clock->componentUpdateNumber(50, ECS::ComponentType::NETWORK)) {
            _network.sendTcpPacket(_sendingPackets[0]);
            if (!_sendingPackets.empty())
                _sendingPackets.pop_front();
        }
    }
}

void Server::Server::checkGameThreads()
{
    while (1) {
        if (_gameServers.empty())
            continue;
        for (size_t i = 0; i < _roomsID.size(); ++i) {
            if (_rooms[_roomsID[i]].get()->getEndGame() == true) {
                _rooms.erase(_roomsID[i]);
                _gameServers[i]->terminate();
                _gameServers[i]->~Thread();
                _gameServers.erase(_gameServers.begin() + i);
                _roomsID.erase(_roomsID.begin() + i);
                break;
            }
        }
    }
}

void Server::Server::connectClients()
{
    _network.connectClients();
}

void Server::Server::empacketRoomAskingList(std::pair<sf::IpAddress, unsigned short> client)
{
    std::deque<std::pair<size_t, std::pair<int, int>>> roomList;
    sf::Packet prepSending;

    for (auto room : _rooms)
        roomList.push_back(std::make_pair(room.first, room.second->getRoomAskingList()));
    prepSending << Network::Networking::ROOMASKING << roomList; // << deque<pair<roomid, pair<place, gen connectés>>;
    _sendingPackets.push_back(std::make_pair(client, prepSending));
}

void Server::Server::checkReady()
{
    sf::Packet prepSending;

    prepSending << Network::Networking::READY;
    std::pair<int, int> pair;
    for (auto room : _rooms) {
        pair = room.second->getRoomAskingList();
        if (pair.second == pair.first) {
            for (auto cli : _clients[room.first])
                _sendingPackets.push_back(std::make_pair(cli, prepSending));
        }
    }
}

/**
 * It's a loop that will check if there's any packet to retrieve, and if there is, it will check what
 * kind of packet it is, and will do the appropriate action
 */
void Server::Server::serverLoop()
{
    _clock->addClockComponent(50, ECS::ComponentType::NETWORK, 10);
    sf::Thread retrieve(&Server::Server::loopPackets, this);
    sf::Thread checkGameThr(&Server::Server::checkGameThreads, this);
    sf::Thread connect(&Server::Server::connectClients, this);
    std::pair<sf::IpAddress, unsigned short> udpClient;
    std::deque<std::pair<sf::IpAddress, unsigned short>> clientList;
    std::shared_ptr<GameServer> instance;
    sf::Packet prepSending;
    int playerId;
    int secondNb = 0;
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> packet;

    connect.launch();
    retrieve.launch();
    checkGameThr.launch();
    while (_up) {
        if (!_retrievedPackets.empty()) {
            packet = _retrievedPackets[0];
            _retrievedPackets.erase(_retrievedPackets.begin());
            std::cout << "LOG : Network Enum received : " << packet.second.first << std::endl;
            if (packet.second.first == Network::Networking::ROOMASKING) {
                empacketRoomAskingList(packet.first);
            } else if (packet.second.first == Network::Networking::ROOMCREATION) { // Renvoyer roomAsking
                packet.second.second >> secondNb;
                if (_roomsID.empty())
                    _roomsID.push_back(0);
                else
                    _roomsID.push_back(_roomsID[_roomsID.size() - 1] + 1);
                _clients[_roomsID[_roomsID.size() - 1]] = std::deque<std::pair<sf::IpAddress, unsigned short>>();
                instance = std::make_shared<GameServer>(secondNb, _roomsID[_roomsID.size() - 1]);
                _rooms.insert(std::make_pair(_roomsID[_roomsID.size() - 1], instance));
                //_rooms[_roomsID[_roomsID.size() - 1]] = instance;
                _gameServers.emplace_back(std::make_shared<sf::Thread>(&GameServer::initGameServer, instance.get()));
                _gameServers[_roomsID.size() - 1]->launch();
                std::cout << "LOG : Creating new room" << std::endl;
                clientList = _network.getClientPair();
                for (auto client : clientList)
                    empacketRoomAskingList(client);
            } else if (packet.second.first == Network::Networking::ROOMCONNECT) { // Renvoyer roomAsking
                packet.second.second >> secondNb >> udpClient;
                prepSending << Network::Networking::CONNECTED << _rooms[secondNb]->addPlayer(udpClient);
                std::cout << "I send it here" << std::endl;
                _sendingPackets.push_back(std::make_pair(packet.first, prepSending));
                _clients[secondNb].push_back(packet.first);
                clientList = _network.getClientPair();
                for (auto client : clientList)
                    empacketRoomAskingList(client);
                checkReady();
            } else if (packet.second.first == Network::Networking::ROOMDISCONNECT) { // Packet : roomID / playerId
                packet.second.second >> secondNb >> playerId;
                if (_rooms[secondNb]->playerDisconnect(playerId)) {
                    clientList = _network.getClientPair();
                    for (auto client : clientList)
                        empacketRoomAskingList(client);
                }
            } else if (packet.second.first == Network::Networking::READY) { // Packet : roomID
                packet.second.second >> secondNb >> playerId;
                _rooms[secondNb]->playerIsReady(playerId);
            }
            prepSending.clear();
        }
    }
    retrieve.terminate();
    checkGameThr.terminate();
    connect.terminate();
    for (size_t i = 0; i < _gameServers.size(); ++i) {
        _gameServers[i]->terminate();
        _gameServers[i]->~Thread();
    }
}