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
#include "PacketOperatorSurcharge.hpp"

Network::Server::~Server()
{
    std::cout << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    std::cout << "          THE SERVER IS ENDING          " << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
}

void Network::Server::createConnection()
{
    if (_udp.bind(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "Failed to launch the server." << std::endl;
        exit(84);
    }
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    std::cout << "         THE SERVER IS STARTING         " << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl << std::endl;
    std::cout << "SERVER INFOS:" << std::endl;
    std::cout << "    IP    : " << sf::IpAddress::getLocalAddress() << std::endl;
    std::cout << "    Port  : " << _udp.getLocalPort() << std::endl << std::endl;
}

std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> Network::Server::retrievePacket()
{
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> message;
    sf::IpAddress ip;
    unsigned short port;
    int type;
    sf::Packet packet;

    if (_udp.receive(packet, ip, port) != sf::Socket::Done) {
        std::cerr << "Failed to receive UDP Packet." << std::endl;
        exit (84);
    }
    message.first = std::make_pair(ip, port);
    packet >> type;
    message.second.first = static_cast<Network::Networking>(type);
    message.second.second = packet;
    std::cout << std::endl << "LOG : Receiving Packet from client" << std::endl;
    //char best[size];
    //std::memcpy(&get, best, size);
    return message;
}

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
