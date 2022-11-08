#include "../Network/NetworkServer.hpp"
#include "../Ecs/IncludeComponents.hpp"
#include "../Ecs/IncludeSystem.hpp"
#include "../Ecs/IncludeCpp.hpp"
#include "../Network/NetworkServer.hpp"
#include "../Graphics/Events.hpp"
#include "../Ecs/Manager.hpp"
#include <memory>
#include <SFML/System.hpp>
#include <list>
#include "surchargeVector.hpp"

#define MAX_ENEMIES 15

namespace Server {
class Server {
public:
    Server();
    ~Server() = default;

    void serverLoop();
    void gameLoop();

private:
    void setManager(std::shared_ptr<Manager> manager);
    ECS::Entity buildPlayer(int playerNb, std::shared_ptr<Manager> manager);
    std::vector<ECS::Entity> buildAllPlayers(std::shared_ptr<Manager> manager, int roomId);
    ECS::Entity buildEnnemy(std::shared_ptr<Manager> manager);
    std::vector<ECS::Entity> buildAllEnnemies(std::shared_ptr<Manager> manager, int maxEnn);
    void loopPackets();
    void checkForEntityDeath(int roomId, std::shared_ptr<Manager> manager, std::vector<ECS::Entity> entities);
    void waitForFilledRoom(int roomId);
    void waitForClientsToBeReady(int roomId);
    void gameUpdate(int roomId, std::shared_ptr<Manager> manager, std::vector<ECS::Entity> entities);
    void updateAll(std::shared_ptr<Manager> manager);
    void getPlayersMove(int roomId, std::vector<ECS::Entity> entities, std::shared_ptr<Manager> manager);

    bool _up;
    int _idArg;
    Network::Server _network;
    std::map<int, int> _players;
    std::vector<int> _roomsID;
    std::shared_ptr<Clock> _clock;
    std::vector<std::pair<std::pair<sf::IpAddress, unsigned short>, sf::Packet>> _sendingPackets;
    std::vector<std::pair<std::pair<sf::IpAddress, unsigned short>, std::pair<Network::Networking, sf::Packet>>> _retrievedPackets;
    std::map<int, std::vector<std::pair<sf::IpAddress, unsigned short>>> _clients;   // vector of clients (pair with ip address and port used) sorted by room id
    std::map<int, std::vector<std::vector<sf::Packet>>> _inGamePackets;    // map containing vector of vector of packet. Usage : map[roomID][playerID(0,1,2,3)][0](retrieving first packet stored for this player in this room)
};
}