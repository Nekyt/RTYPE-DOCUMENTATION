/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameClient
*/

#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include "../Graphics/InitSfml.hpp"
#include "../Network/NetworkClient.hpp"
#include "../Network/Enum.hpp"
#include <SFML/System.hpp>
#include "../Ecs/Manager.hpp"
#include "../Ecs/Clock.hpp"

enum GameState
{
    Menu,
    Game,
    Options,
};

class GameClient {
public:
    GameClient(const char* ip, unsigned short port);
    ~GameClient() = default;

        void setSfml();

        void loadSystems();
        void gameLoop();
        void handleEvents(const sf::Event &event);
        void mouseMenu(const sf::Event &event);
        void handleEventsMouse(const sf::Event &event);
        void handleEventsKey(std::deque<Button> eventKey);
        void initConnection(int roomId);
        void handleEventsTextEntered(const sf::Event &event);
        void retrievePackets();
        void empacketing(Network::Networking net);

        void selectMode();

        void loadMenu();
        void manageMenu();

        void loadGame();
        void waitEnum(Network::Networking net);
        void manageGame();

protected:
private:
    std::shared_ptr<InitSfml> _graphical;
    GameState _state;
    Manager _manager;
    Events _events;
    std::shared_ptr<Clock> _clock;
    std::shared_ptr<Clock> _networkClock;
    std::deque<Button> _gameCommandsList;
    int _roomId;
    int _playerID;
    int _graphEntitiesCount;

    std::deque<std::shared_ptr<ECS::Sprite>> _spriteMenu;
    std::deque<std::shared_ptr<ECS::Text>> _textMenu;

    Network::Client _cli;
    std::deque<sf::Packet> _retrievedPackets;
    std::deque<sf::Packet> _sendingPackets;
    sf::Sprite _sprite;
    bool _retrieving;
    bool _isInGame;
    bool _nbrPlayersInGameReached;
};

#endif /* !GAMECLIENT_HPP_ */
