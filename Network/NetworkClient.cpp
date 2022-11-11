/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** NetworkClient
*/

#include "NetworkClient.hpp"
#include "Enum.hpp"
#include <memory>
#include <cstring>
#include <unistd.h>
#include "PacketOperatorSurcharge.hpp"

/**
 * It creates a UDP socket, binds it to a random port, and adds it to the selector
 *
 * @param ip the ip of the server
 * @param port the port to bind the socket to
 */
Network::Client::Client(const char* ip, unsigned short port)
    : _ip(ip)
    , _port(port)
{
    if (_udp.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "ERROR : Fail to launch client Network." << std::endl;
        exit (84);
    }
    _selector.add(_udp);
    _udp.setBlocking(false);
    printf("listening on port %d\n", _udp.getLocalPort());
}

/**
 * It receives a packet from the server and returns it
 *
 * @return A packet.
 */
sf::Packet Network::Client::retrievePacket()
{
    sf::Packet packet;
    sf::IpAddress ip = _ip;
    unsigned short port = _port;
    sf::Socket::Status status = _udp.receive(packet, ip, port);

    if (status == sf::Socket::Error) {
        std::cerr << "ERROR : Fail to receive request in Network::Client::retrievePacket." << std::endl;
        exit (84);
    }
    return packet;
}

int Network::Client::getRoomId() const
{
    return (_roomId);
}

/**
 * It sends a packet to the server to create a room with the number of players specified in the
 * parameter
 *
 * @param players The number of players in the room.
 */
void Network::Client::roomCreation(int players)
{
    sf::Packet packet;
    sf::IpAddress ip = _ip;
    unsigned short port = _port;

    packet << Network::Networking::ROOMCREATION << players;
    if (_udp.send(packet, ip, port) != sf::Socket::Done) {
        std::cerr << "ERROR : Fail to send a request." << std::endl;
        exit (84);
    }
}

/**
 * It sends a request to the server to join a room, and if it fails, it creates a new room and tries to
 * join it
 *
 * @param rooms a deque of int, which contains the rooms' id.
 *
 * @return The playerID
 */
int Network::Client::joinRoom(std::deque<int> rooms)
{
    sf::Packet packet;
    int playerID = 0;
    std::string error;
    int type;
    sf::UdpSocket::Status status;
    sf::IpAddress ip = _ip;
    unsigned short port = _port;

    for (int i = 0; i < rooms.size(); ++i) {
        packet << Network::Networking::ROOMCONNECT << static_cast<int>(i);
        if (_udp.send(packet, ip, port) != sf::Socket::Done) {
            std::cerr << "ERROR : Fail to send a request in Network::Client::joinRoom." << std::endl;
            exit (84);
        }
        std::cout << "SENDING ROOMCONNECT" << std::endl;
        packet.clear();
        status = _udp.receive(packet, ip, port);
        while (status != sf::Socket::Done) {
            if (status == sf::UdpSocket::Status::Error)
                std::cerr << "ERROR : Fail to retrieve a request in Network::Client::joinRoom." << std::endl;
            status = _udp.receive(packet, ip, port);
        }
        packet >> type;
        if (type == Network::Networking::CONNECTED) {
            _roomId = i;
            break;
        } else if (type == Network::Networking::ERROR) {
            packet >> error;
            std::cerr << "ERROR : " << error << std::endl;
        }
        packet.clear();
    }
    if (type == Network::Networking::ERROR) {
        roomCreation(4);
        return joinRoom(roomAskingList());
    }
    packet >> playerID;
    return playerID;
}

/**
 * It sends a request to the server to get the list of rooms, and then it receives the list of rooms
 *
 * @return A deque of int.
 */
std::deque<int> Network::Client::roomAskingList()
{
    sf::Packet packet;
    int type;
    std::deque<int> vec;
    sf::UdpSocket::Status status;
    sf::IpAddress ip = _ip;
    unsigned short port = _port;

    packet << Network::Networking::ROOMASKING;
    if (_udp.send(packet, ip, port) == sf::Socket::Error) {
        std::cerr << "ERROR : Fail to send a request in Network::Client::roomAskingList." << std::endl;
        exit (84);
    }
    packet.clear();
    status = _udp.receive(packet, ip, port);
    while (status != sf::Socket::Done) {
        if (status == sf::UdpSocket::Status::Error)
            std::cerr << "ERROR : Fail to retrieve a request in Network::Client::joinRoom." << std::endl;
        status = _udp.receive(packet, ip, port);
    }
    packet >> type >> vec;
    return vec;
}

/**
 * It sends a packet to the server
 *
 * @param packet The packet to send.
 */
int Network::Client::sendPacket(sf::Packet packet)
{
    int net;
    sf::Packet copy;
    sf::IpAddress ip = _ip;
    unsigned short port = _port;
    sf::Socket::Status status = _udp.send(packet, ip, port);
    if (status == sf::Socket::Error) {
        copy = packet;
        copy >> net;
        std::cout << "ERROR : Fail to send the request : " << net << " UDP Status : " << status << " Packet size : " << packet.getDataSize() << std::endl << "Trying again in a second..." << std::endl;
        sleep(1);
        return -1;
    }
    packet >> net;
    std::cout << "Sending enum : " << net << std::endl;
    return 0;
}