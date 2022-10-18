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
#include "PacketOperatorSurcharge.hpp"

/**
 * It creates a client socket and binds it to a random port
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
    printf("lisening on port %d\n", _udp.getLocalPort());
}

/**
 * It receives a packet from the server and returns it
 *
 * @return A packet
 */
sf::Packet Network::Client::retrievePacket()
{
    sf::Packet packet;

    if (_udp.receive(packet, _ip, _port) != sf::Socket::Done) {
        std::cerr << "ERROR : Fail to receive request" << std::endl;
        exit (84);
    }
    return packet;
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

    packet << Network::Networking::ROOMCREATION << players;
    if (_udp.send(packet, _ip, _port) != sf::Socket::Done) {
        std::cerr << "ERROR : Fail to in sending a request." << std::endl;
        exit (84);
    }
}

/**
 * It sends a request to the server to get the list of rooms, and then it receives the list of rooms
 *
 * @return A vector of int.
 */
std::vector<int> Network::Client::roomAskingList()
{
    sf::Packet packet;
    int type;
    std::vector<int> vec;

    packet << Network::Networking::ROOMASKING;
    if (_udp.send(packet, _ip, _port) != sf::Socket::Done) {
        std::cerr << "ERROR : Fail to send a request." << std::endl;
        exit (84);
    }
    packet.clear();
    if (_udp.receive(packet, _ip, _port) != sf::Socket::Done) {
        std::cerr << "ERROR : Fail to retrieve a request." << std::endl;
        exit (84);
    }
    packet >> type >> vec;
    return vec;
}

/**
 * It sends a request to the server to join a room, and if it fails, it creates a new room and tries to
 * join it
 *
 * @param rooms a vector of int, which contains the rooms' id.
 *
 * @return The playerID
 */
int Network::Client::joinRoom(std::vector<int> rooms)
{
    sf::Packet packet;
    int playerID = 0;
    std::string error;
    int type;

    for (int i = 0; i < rooms.size(); ++i) {
        packet << Network::Networking::ROOMCONNECT << static_cast<int>(i);
        if (_udp.send(packet, _ip, _port) != sf::Socket::Done) {
            std::cerr << "ERROR : Fail to send a request" << std::endl;
            exit (84);
        }
        packet.clear();
        if (_udp.receive(packet, _ip, _port) != sf::Socket::Done) {
            std::cerr << "ERROR : Fail to retrieve a request." << std::endl;
            exit (84);
        }
        packet >> type;
        if (type == Network::Networking::CONNECTED) {
            _roomId = i;
            break;
        }
        packet >> error;
        std::cerr << "ERROR : " << error << std::endl;
    }
    if (type == Network::Networking::ERROR) {
        roomCreation(4);
        return joinRoom(roomAskingList());
    }
    packet >> playerID;
    return playerID;
}

/**
 * It sends a packet containing the size of the list of buttons and the list of buttons itself
 *
 * @param buttons a list of buttons that the player pressed
 */
void Network::Client::sendPlayerUpdate(std::vector<Button> buttons)
{
    char buff[sizeof(std::list<Button>[buttons.size()])];
    sf::Packet packet;

    packet << Network::Networking::PLAYERUPDATE << static_cast<int>(sizeof(std::list<Button>[buttons.size()]));
    memcpy(&buff, &buttons, sizeof(std::list<Button>[buttons.size()]));
    if (_udp.send(packet, _ip, _port) != sf::Socket::Done) {
        std::cerr << "ERROR : " << std::endl;
        exit(84);
    }

}

/**
 * It sends a packet to the server to tell him that the client is ready to play
 */
void Network::Client::sendReady()
{
    sf::Packet packet;

    packet << Network::Networking::READY << static_cast<int>(_roomId);
    if (_udp.send(packet, _ip, _port) != sf::Socket::Done) {
        std::cerr << "ERROR : Fail to send a request" << std::endl;
        exit (84);
    }
    packet.clear();
}