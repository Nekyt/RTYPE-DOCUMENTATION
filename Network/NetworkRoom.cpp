/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** Network::Room
*/

#include "NetworkRoom.hpp"
#include <any>
#include <memory>
#include <cstring>

/**
 * It's the destructor for the Room class
 */
Network::Room::~Room()
{
    std::cout << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    std::cout << "          THE ROOM " << _roomId << " IS ENDING          " << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
}

/**
 * It creates a connection between the Room and the client.
 */
void Network::Room::createConnection(int roomId)
{
    if (_udp.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "Failed to launch udp for the room." << std::endl;
        exit(84);
    }
    _roomId = roomId;
    _udp.setBlocking(false);
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    std::cout << "         NEW ROOM IS STARTING         " << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl << std::endl;
    std::cout << "  ROOM INFOS :" << std::endl;
    std::cout << "    IP      : " << sf::IpAddress::getLocalAddress() << std::endl;
    std::cout << "    Port    : " << _udp.getLocalPort() << std::endl << std::endl;
    std::cout << "    RoomID  : " << roomId << std::endl << std::endl;
}

/**
 * It receives a packet from the client, and returns a pair of pair of IpAddress and unsigned short, and a pair of Networking and sf::Packet
 *
 * @return A pair of pair of IpAddress and unsigned short, and a pair of Networking and sf::Packet
 */
std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> Network::Room::retrievePacket()
{
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> message;
    sf::IpAddress ip;
    unsigned short port;
    int type;
    sf::Packet packet;

    if (_udp.receive(packet, ip, port) == sf::Socket::Error) {
        std::cerr << "Failed to receive UDP Packet." << std::endl;
        exit (84);
    }
    message.first = std::make_pair(ip, port);
    if (packet.getDataSize()) {
        packet >> type;
        message.second.first = static_cast<Network::Networking>(type);
        message.second.second = packet;
        std::cout << std::endl << "LOG : Receiving Packet from client" << std::endl;
    } else {
        message.second.first = Network::Networking::ERROR;
        message.second.second = packet;
    }
    return message;
}


/**
 * It sends a packet to a client
 *
 * @param client The client to send the packet to.
 * @param packet The packet to send
 */
void Network::Room::sendPacket(std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet> packet)
{
    if (_udp.send(packet.second, packet.first.first, packet.first.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
    } else
        std::cout << std::endl << "LOG : Sending a packet to a Client." << std::endl;
}

/**
 * It sends an error message to a client
 *
 * @param client The client to send the error to.
 * @param errorMsg The error message to send to the client.
 */
void Network::Room::sendError(std::pair<sf::IpAddress, unsigned short> client, std::string errorMsg)
{
    sf::Packet packet;

    packet << Network::Networking::ERROR << errorMsg;
    if (_udp.send(packet, client.first, client.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
        exit (84);
    }
    std::cout << std::endl << "LOG : Sending Error Code to Player" << std::endl;
}