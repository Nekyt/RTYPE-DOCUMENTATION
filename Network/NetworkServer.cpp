/*
** EPITECH PROJECT, 2022
** B-CPP-500-STG-5-1-rtype-romanie.de-meyer
** File description:
** Network::Server
*/

#include "NetworkServer.hpp"
#include "PacketOperatorSurcharge.hpp"
#include <any>
#include <cstring>
#include <memory>

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
 * It creates a connection and prints the server's IP and port
 */
void Network::Server::createConnection()
{
    if (_listener.listen(sf::Socket::AnyPort) != sf::Socket::Done) {
        std::cerr << "Failed to listen." << std::endl;
        exit(84);
    }
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
    std::cout << "         THE SERVER IS STARTING         " << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << std::endl << std::endl;
    std::cout << "SERVER INFOS:" << std::endl;
    std::cout << "    IP    : " << sf::IpAddress::getLocalAddress() << std::endl;
    std::cout << "    Port  : " << _listener.getLocalPort() << std::endl << std::endl;
}

/**
 * It waits for a client to connect, then adds it to the selector and the client array
 */
void Network::Server::connectClients()
{
    _isTcpUp = true;
    _selector.add(_listener);

    while (_isTcpUp) {
        if (_selector.wait(sf::milliseconds(10))) {
            if (_selector.isReady(_listener)) {
                sf::TcpSocket *newClient = new sf::TcpSocket();
                if (_listener.accept(*newClient) == sf::Socket::Done) {
                    newClient->setBlocking(false);
                    _clientArray.push_back(newClient);
                    _clientPair.push_back(std::make_pair<sf::IpAddress, unsigned short>(newClient->getRemoteAddress(), newClient->getRemotePort()));
                    _selector.add(*newClient);
                    std::cout << "Added client " << newClient->getRemoteAddress() << ":" << newClient->getRemotePort() << std::endl;
                } else {
                    delete(newClient);
                    break;
                }
            } /*else {
                managePackets();
            }*/
        }
    }
}

/**
 * It disconnects the client from the socket and removes it from the client array.
 *
 * @param socket The socket to disconnect.
 * @param pos The index of this socket in the array.
*/
void Network::Server::disconnectClient(sf::TcpSocket *socket, size_t pos)
{
    std::cout << "Client " << socket->getRemoteAddress() << ":" << socket->getRemotePort() << " disconnected" << std::endl;
    socket->disconnect();
    _clientArray.erase(_clientArray.begin() + pos);
    _clientPair.erase(_clientPair.begin() + pos);
}


/**
 * It loops through all the clients and checks if they have sent a packet. If they have, it returns the
 * packet
 *
 * @return A pair of pairs of sf::IpAddress and unsigned short, and a pair of Network::Networking and
 * sf::Packet.
 */
std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> Network::Server::retrieveTcpPacket()
{
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> message;
    sf::Packet error;

    if (_selector.wait(sf::milliseconds(10))) {
        for (size_t i = 0; i < _clientArray.size(); i++) {
            if (_selector.isReady(*(_clientArray[i]))) {
                return receivePacket(_clientArray[i], i);
            }
        }
    }
    message.second.first = Network::Networking::ERROR;
    message.second.second = error;
    return message;
}

/**
 * It receives a packet from the specified client, and returns a pair of pair of IpAddress and unsigned short, and a pair of Networking and sf::Packet
 *
 * @return A pair of pair of IpAddress and unsigned short, and a pair of Networking and sf::Packet
 */
std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> Network::Server::receivePacket(sf::TcpSocket *client, size_t iterator)
{
    sf::Packet packet;
    std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>> message;
    int type;
    sf::Socket::Status status = client->receive(packet);

    if (status == sf::Socket::Error) {
        std::cerr << "Failed to receive TCP packet." << std::endl;
        exit(84);
    }
    message.first = std::make_pair(client->getRemoteAddress(), client->getRemotePort());
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
void Network::Server::sendTcpPacket(std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet> packet)
{
    size_t i = 0;
    for (; i < _clientPair.size() && (packet.first.first != _clientPair[i].first || packet.first.second != _clientPair[i].second); ++i);
    if (i >= _clientPair.size()) {
        std::cerr << "ERROR : Not a client." << std::endl;
        return;
    }
    std::cout << "Client : " << i << std::endl;
    while (_clientArray[i]->send(packet.second) != sf::Socket::Done) {
        std::cerr << "Failed to send TCP Packet." << std::endl;
    }
    std::cout << std::endl << "LOG : Sending a packet to a Client." << std::endl;
}

std::deque<std::pair<sf::IpAddress, unsigned short>> Network::Server::getClientPair() const
{
    return _clientPair;
}