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
#include <SFML/System.hpp>

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

<<<<<<< Updated upstream
        void loadComponents();
        void loadSystems();
        void gameLoop();
        void handleEvents(const sf::Event &event);
        void mouseMenu(const sf::Event &event);
        void handleEventsMouse(const sf::Event &event);
        void handleEventsKey(Button eventKey);
    void initConnection(int roomId);
        void handleEventsTextEntered(const sf::Event &event);
    void retreivePackets();

        void selectMode();
=======
    void loadComponents();
    void loadSystems();
    void gameLoop();
    void handleEvents(const sf::Event& event);
    void mouseMenu(const sf::Event& event);
    void handleEventsMouse(const sf::Event& event);
    void handleEventsKey(Button eventKey);
    void initConnection(int roomId);

    void sendCommandsToServer();
    void retreivePackets();
>>>>>>> Stashed changes

        void loadMenu();
        void manageMenu();

        void loadGame();
        void manageGame();

protected:
private:
    std::shared_ptr<InitSfml> _graphical;
    GameState _state;
    Manager _manager;
    Events _events;
    std::shared_ptr<Clock> _clock;
    std::vector<Button> _gameCommandsList;
    int _roomId;

    std::vector<std::shared_ptr<ECS::Sprite>> _spriteMenu;
    std::vector<std::shared_ptr<ECS::Text>> _textMenu;

    Network::Client _cli;
    std::vector<sf::Packet> _packets;
    sf::Sprite _sprite;
    bool _retrieving;
    bool _isInGame;
    bool _nbrPlayersInGameReached;
};

#endif /* !GAMECLIENT_HPP_ */
