#include "../Network/NetworkServer.hpp"
#include "../Ecs/IncludeComponents.hpp"
#include "../Ecs/IncludeSystem.hpp"
#include "../Ecs/IncludeCpp.hpp"
#include "../Network/NetworkServer.hpp"
#include "../Ecs/Manager.hpp"
#include "../Graphics/Events.hpp"
#include <list>

namespace Server {
class Server {
public:
    Server();
    ~Server() = default;

    void serverLoop();
    void gameLoop();

private:
    void setManager(std::shared_ptr<Manager>, int roomId);
    void waitForFilledRoom(int roomId);
    void waitForClientsToBeReady(int roomId);
    void gameUpdate(int roomId, std::shared_ptr<Manager> manager);
    void updateAll(std::shared_ptr<Manager> manager);

    bool _up;
    int _idArg = -1;
    Network::Server _network;
    std::map<int, int> _players;
    std::vector<int> _roomsID;
    std::map<int, std::vector<std::pair<sf::IpAddress, unsigned short>>> _clients;   // vector of clients (pair with ip address and port used) sorted by room id
    std::map<int, std::vector<std::vector<sf::Packet>>> _inGamePackets;    // map containing vector of vector of packet. Usage : map[roomID][playerID(0,1,2,3)][0](retrieving first packet stored for this player in this room)
};
}