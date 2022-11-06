/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** Network::Server
*/

#include "NetworkServer.hpp"
#include <any>
#include <memory>
#include <cstring>

/**
 * It's the destructor for the Server class
 */
Network::Server::~Server()
{
    std::cout << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    std::cout << "          THE SERVER IS ENDING          " << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
}

/**
 * It creates a connection between the server and the client.
 */
void Network::Server::createConnection()
{
    if (_udp.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "Failed to launch the server." << std::endl;
        exit(84);
    }
    _udp.setBlocking(false);
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    std::cout << "         THE SERVER IS STARTING         " << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl << std::endl;
    std::cout << "SERVER INFOS:" << std::endl;
    std::cout << "    IP    : " << sf::IpAddress::getLocalAddress() << std::endl;
    std::cout << "    Port  : " << _udp.getLocalPort() << std::endl << std::endl;
}

/**
 * It receives a packet from the client, and returns a pair of pair of IpAddress and unsigned short, and a pair of Networking and sf::Packet
 *
 * @return A pair of pair of IpAddress and unsigned short, and a pair of Networking and sf::Packet
 */
std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> Network::Server::retrievePacket()
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
void Network::Server::sendPacket(std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet> packet)
{
    if (_udp.send(packet.second, packet.first.first, packet.first.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
        exit (84);
    }
    std::cout << std::endl << "LOG : Sending a packet to a Client." << std::endl;
}


/**
 * It sends the player id to the client
 *
 * @param client The client to send the packet to.
 * @param id The id of the player
 */
void Network::Server::sendPlayerId(std::pair<sf::IpAddress, unsigned short> client, int id)
{
    sf::Packet packet;

    packet << Network::Networking::CONNECTED << id;
    if (_udp.send(packet, client.first, client.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
        exit (84);
    }
    std::cout << std::endl << "LOG : Sending Player ID to Client" << std::endl;
}

/**
 * It sends the room list to the client
 *
 * @param client The client's IP address and port.
 * @param roomId The id of the room you want to send to the client.
 */
void Network::Server::sendRoomList(std::pair<sf::IpAddress, unsigned short> client, std::vector<int> roomId)
{
    sf::Packet packet;

    packet << Network::Networking::ROOMASKING << roomId;
    if (_udp.send(packet, client.first, client.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
        exit (84);
    }
    std::cout << std::endl << "LOG : Sending Room List to Client" << std::endl;
}

/**
 * It sends an error message to a client
 *
 * @param client The client to send the error to.
 * @param errorMsg The error message to send to the client.
 */
void Network::Server::sendError(std::pair<sf::IpAddress, unsigned short> client, std::string errorMsg)
{
    sf::Packet packet;

    packet << Network::Networking::ERROR << errorMsg;
    if (_udp.send(packet, client.first, client.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
        exit (84);
    }
    std::cout << std::endl << "LOG : Sending Error Code to Client" << std::endl;
}

/**
 * It sends an enum to the client
 *
 * @param client The client to send the packet to.
 * @param type The type of packet you want to send.
 */
void Network::Server::sendEnum(std::pair<sf::IpAddress, unsigned short> client, Network::Networking type)
{
    sf::Packet packet;

    packet << type;
    if (_udp.send(packet, client.first, client.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
        exit (84);
    }
    std::cout << std::endl << "LOG : Sending Enum NetworkType to Client" << std::endl;
}


/**
 * It sends the game update to the client
 *
 * @param client The client to send the packet to.
 * @param ent A vector of pairs of Entity and Position.
 */
void Network::Server::sendGameUpdate(std::pair<sf::IpAddress, unsigned short> client, std::vector<std::pair<ECS::Entity, ECS::Position>> ent)
{
    sf::Packet packet;

    packet << Network::Networking::GAMEUPDATE << ent;
    if (_udp.send(packet, client.first, client.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
        exit (84);
    }
    std::cout << std::endl << "LOG : Sending Entities Positions to Client" << std::endl;
}

/**
 * It sends a packet to a client to tell him that a player has died or disconnected.
 *
 * @param client The client to send the packet to.
 * @param id The id of the player that died or disconnected.
 * @param type The type of packet we're sending.
 */
void Network::Server::sendPlayerDeathOrDisconnect(std::pair<sf::IpAddress, unsigned short> client, int id, Network::Networking type)
{
    sf::Packet packet;

    packet << type << id;
    if (_udp.send(packet, client.first, client.second) != sf::Socket::Done) {
        std::cerr << "Failed to send UDP Packet." << std::endl;
        exit (84);
    }
    if (type == Network::Networking::PLAYERDEATH)
        std::cout << std::endl << "LOG : Sending Player Death to Client" << std::endl;
    else
        std::cout << std::endl << "LOG : Sending Player Disconnection to Client" << std::endl;
}
