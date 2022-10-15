/*
** EPITECH PROJECT, 2022
** r-type
** File description:
** GameClient
*/

#ifndef GAMECLIENT_HPP_
#define GAMECLIENT_HPP_

#include "../Ecs/Manager.hpp"
#include "../Graphics/Events.hpp"
#include "../Graphics/InitSfml.hpp"

enum GameState {
    Menu,
    Game,
    Options,
};

class GameClient {
public:
    GameClient();
    ~GameClient() = default;

    void setSfml();

    void loadComponents();
    void loadSystems();
    void gameLoop();
    void handleEvents(const sf::Event& event);
    void mouseMenu(const sf::Event& event);
    void handleEventsMouse(const sf::Event& event);
    void handleEventsKey(Button eventKey);

    void sendCommandsToServer();

    void selectMode();

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
    std::list<Button> _gameCommandsList;

    sf::Sprite _sprite;
    bool _isInGame;
    bool _nbrPlayersInGameReached;
};

#endif /* !GAMECLIENT_HPP_ */
